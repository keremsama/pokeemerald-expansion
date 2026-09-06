#!/usr/bin/env python3
from __future__ import annotations

import argparse
import collections
import hashlib
import json
import re
from dataclasses import dataclass
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
DEFAULT_INPUT = ROOT / "competitive_builds_frontier_compact.json"
CONSTANTS_OUT = ROOT / "include/constants/battle_frontier_mons.h"
MONS_OUT = ROOT / "src/data/battle_frontier/battle_frontier_mons.h"
TRAINER_MONS_OUT = ROOT / "src/data/battle_frontier/battle_frontier_trainer_mons.h"
BRAIN_MONS_OUT = ROOT / "src/data/battle_frontier/battle_frontier_brain_mons.h"
REPORT_OUT = ROOT / "battle_frontier_generation_report.txt"
TRAINERS_FILE = ROOT / "src/data/battle_frontier/battle_frontier_trainers.h"

STAT_ORDER = ("hp", "atk", "def", "spe", "spa", "spd")
SOURCE_PRIORITY = {
    "pokemon_champions": 0,
    "smogon": 1,
    "showdown": 2,
    "showdown_randbats_gen9": 3,
    "showdown_randbats_gen8": 4,
    "showdown_randbats_gen7": 5,
    "custom_missingmon": 6,
}
NON_MEGA_ITE_ITEMS = {
    "ITEM_EVIOLITE",
}
TERA_SPECIFIC_SPECIES = {
    "SPECIES_TERAPAGOS",
    "SPECIES_TERAPAGOS_NORMAL",
    "SPECIES_TERAPAGOS_TERASTAL",
    "SPECIES_TERAPAGOS_STELLAR",
}
TERA_SPECIFIC_ABILITIES = {
    "ABILITY_TERA_SHIFT",
    "ABILITY_TERA_SHELL",
    "ABILITY_TERAFORM_ZERO",
}
TERA_SPECIFIC_MOVES = {
    "MOVE_TERA_BLAST",
    "MOVE_TERA_STARSTORM",
}

RANK_DESCRIPTIONS = {
    0: "LC builds",
    1: "NFE builds",
    2: "ZU/PU/random battle/missingmon builds",
    3: "NU/RU/National Dex RU/Champions D builds",
    4: "UU/National Dex UU/Champions C builds",
    5: "OU/Battle Stadium/National Dex/Champions B builds",
    6: "Main-pool Mega Stone and Champions S/A builds",
}

TYPE_THEMES = {
    "WATER": {"TYPE_WATER"},
    "FIRE": {"TYPE_FIRE"},
    "GRASS": {"TYPE_GRASS"},
    "BUG": {"TYPE_BUG"},
    "FLYING": {"TYPE_FLYING"},
    "ELECTRIC": {"TYPE_ELECTRIC"},
    "POISON": {"TYPE_POISON"},
    "FIGHTING": {"TYPE_FIGHTING"},
    "PSYCHIC": {"TYPE_PSYCHIC"},
    "STEEL": {"TYPE_STEEL"},
    "GHOST_DARK": {"TYPE_GHOST", "TYPE_DARK"},
    "DRAGON": {"TYPE_DRAGON"},
    "ROCK_GROUND_STEEL": {"TYPE_ROCK", "TYPE_GROUND", "TYPE_STEEL"},
    "GRASS_FAIRY_POISON": {"TYPE_GRASS", "TYPE_FAIRY", "TYPE_POISON"},
    "OUTDOOR": {"TYPE_GRASS", "TYPE_GROUND", "TYPE_ROCK", "TYPE_FIRE", "TYPE_WATER"},
    "CUTE": {"TYPE_NORMAL", "TYPE_FAIRY", "TYPE_ELECTRIC", "TYPE_WATER", "TYPE_GRASS"},
    "RARE": {"TYPE_DRAGON", "TYPE_PSYCHIC", "TYPE_STEEL", "TYPE_DARK", "TYPE_FAIRY"},
}

EEVEELUTION_SPECIES = {
    "SPECIES_VAPOREON",
    "SPECIES_JOLTEON",
    "SPECIES_FLAREON",
    "SPECIES_ESPEON",
    "SPECIES_UMBREON",
    "SPECIES_LEAFEON",
    "SPECIES_GLACEON",
    "SPECIES_SYLVEON",
}

BRAIN_TEAMS = {
    "TOWER": [
        [("Kingambit", None), ("Garchomp", None), ("Sinistcha", None)],
        [("Mewtwo", "ITEM_MEWTWONITE_Y"), ("Zacian-Crowned", None), ("Kyogre", None)],
    ],
    "DOME": [
        [("Charizard", "ITEM_CHARIZARDITE_Y"), ("Swampert", "ITEM_SWAMPERTITE"), ("Metagross", "ITEM_METAGROSSITE")],
        [("Koraidon", None), ("Miraidon", None), ("Rayquaza", None)],
    ],
    "PALACE": [
        [("Arcanine-Hisui", None), ("Slowking-Galar", None), ("Milotic", None)],
        [("Ho-Oh", None), ("Lugia", None), ("Giratina", None)],
    ],
    "ARENA": [
        [("Heracross", "ITEM_HERACRONITE"), ("Kommo-o", None), ("Breloom", None)],
        [("Marshadow", None), ("Zamazenta-Crowned", None), ("Urshifu", None)],
    ],
    "FACTORY": [
        [("Metagross", None), ("Skarmory", None), ("Aggron", "ITEM_AGGRONITE")],
        [("Metagross", "ITEM_METAGROSSITE"), ("Skarmory", None), ("Aggron", "ITEM_AGGRONITE")],
    ],
    "PIKE": [
        [("Seviper", None), ("Milotic", None), ("Glimmora", "ITEM_GLIMMORANITE")],
        [("Zygarde", None), ("Eternatus", None), ("Yveltal", None)],
    ],
    "PYRAMID": [
        [("Regirock", None), ("Regice", None), ("Registeel", None)],
        [("Groudon", None), ("Kyogre", None), ("Rayquaza", None)],
    ],
}

BRAIN_SILVER_IVS = {
    "TOWER": "24",
    "DOME": "20",
    "PALACE": "16",
    "ARENA": "20",
    "FACTORY": "MAX_PER_STAT_IVS",
    "PIKE": "16",
    "PYRAMID": "16",
}


@dataclass(frozen=True)
class SpeciesMeta:
    types: frozenset[str]
    bst: int | None
    is_legendary: bool
    is_mythical: bool
    is_ultra_beast: bool
    is_paradox: bool
    is_frontier_banned: bool


@dataclass(frozen=True)
class Entry:
    mon_id: int
    const_name: str
    species_name: str
    species_const: str
    source_form: str
    set_name: str
    source: str
    format_name: str
    rank: int
    pool: str
    move_consts: tuple[str, str, str, str]
    item_const: str
    ability_const: str
    nature_const: str
    evs: tuple[int, int, int, int, int, int]
    types: frozenset[str]
    is_mega_set: bool


def collect_project_constants(root: Path) -> set[str]:
    constants: set[str] = set()
    for path in (root / "include/constants").rglob("*.h"):
        text = path.read_text()
        constants.update(re.findall(r"^\s*#define\s+([A-Z][A-Z0-9_]+)\b", text, re.M))
    return constants


def parse_species_aliases(root: Path) -> dict[str, str]:
    aliases: dict[str, str] = {}
    text = (root / "include/constants/species.h").read_text()
    for match in re.finditer(r"^\s*#define\s+(SPECIES_[A-Z0-9_]+)\s+(SPECIES_[A-Z0-9_]+)\b", text, re.M):
        aliases[match.group(1)] = match.group(2)
    return aliases


def resolve_species_alias(species: str, aliases: dict[str, str]) -> str:
    seen: set[str] = set()
    while species in aliases and species not in seen:
        seen.add(species)
        species = aliases[species]
    return species


def parse_species_meta(root: Path) -> dict[str, SpeciesMeta]:
    meta_by_species: dict[str, SpeciesMeta] = {}

    for path in sorted((root / "src/data/pokemon/species_info").glob("gen_*_families.h")):
        text = path.read_text()
        species_info_macros = parse_species_info_macros(text)
        current_species: str | None = None
        pending_lines: list[str] = []

        for line in text.splitlines():
            match = re.match(r"\s*\[(SPECIES_[A-Z0-9_]+)\]\s*=", line)
            if match:
                if current_species and pending_lines:
                    _store_species_meta(meta_by_species, current_species, "\n".join(pending_lines))
                current_species = match.group(1)
                pending_lines = []
                macro_match = re.search(r"=\s*([A-Z][A-Z0-9_]+)\s*\(", line)
                if macro_match and macro_match.group(1) in species_info_macros:
                    _store_species_meta(meta_by_species, current_species, species_info_macros[macro_match.group(1)])
                    current_species = None
                continue
            if current_species:
                pending_lines.append(line)

        if current_species and pending_lines:
            _store_species_meta(meta_by_species, current_species, "\n".join(pending_lines))

    aliases = parse_species_aliases(root)
    for alias, target in aliases.items():
        resolved = resolve_species_alias(target, aliases)
        if resolved in meta_by_species:
            meta_by_species[alias] = meta_by_species[resolved]

    return meta_by_species


def parse_species_info_macros(text: str) -> dict[str, str]:
    macros: dict[str, str] = {}
    lines = text.splitlines()
    i = 0
    while i < len(lines):
        match = re.match(r"\s*#define\s+([A-Z][A-Z0-9_]+)\s*\([^)]*\)\s*(.*)", lines[i])
        if not match:
            i += 1
            continue

        name = match.group(1)
        body_lines = [match.group(2).rstrip("\\").strip()]
        while lines[i].rstrip().endswith("\\") and i + 1 < len(lines):
            i += 1
            body_lines.append(lines[i].rstrip("\\").strip())
        macros[name] = "\n".join(body_lines)
        i += 1
    return macros


def _store_species_meta(meta_by_species: dict[str, SpeciesMeta], species: str, body: str) -> None:
    match = re.search(r"\.types\s*=\s*MON_TYPES\(([^)]*)\)", body)
    type_names = frozenset(re.findall(r"TYPE_[A-Z0-9_]+", match.group(1))) if match else frozenset()
    stats = []
    for field in ("baseHP", "baseAttack", "baseDefense", "baseSpeed", "baseSpAttack", "baseSpDefense"):
        stat_match = re.search(rf"\.{field}\s*=\s*(\d+)", body)
        if stat_match:
            stats.append(int(stat_match.group(1)))
    bst = sum(stats) if len(stats) == 6 else None
    meta_by_species[species] = SpeciesMeta(
        types=type_names,
        bst=bst,
        is_legendary=".isLegendary = TRUE" in body,
        is_mythical=".isMythical = TRUE" in body,
        is_ultra_beast=".isUltraBeast = TRUE" in body,
        is_paradox=".isParadox = TRUE" in body,
        is_frontier_banned=".isFrontierBanned = TRUE" in body,
    )


def is_mega_stone_item(item_const: str) -> bool:
    return bool(re.fullmatch(r"ITEM_[A-Z0-9_]+ITE(?:_[XYZ])?", item_const)) and item_const not in NON_MEGA_ITE_ITEMS


def tera_specific_hits(species_const: str, ability_const: str, move_consts: tuple[str, str, str, str]) -> list[str]:
    hits: list[str] = []
    if species_const in TERA_SPECIFIC_SPECIES:
        hits.append(species_const)
    if ability_const in TERA_SPECIFIC_ABILITIES:
        hits.append(ability_const)
    hits.extend(move for move in move_consts if move in TERA_SPECIFIC_MOVES)
    return sorted(set(hits))


def adjusted_rank_and_pool(build: dict, species_meta: SpeciesMeta | None, item_const: str) -> tuple[int, str]:
    pool = build_pool(build)
    rank = explicit_rank(build)
    if rank is None:
        rank = build_rank(build, item_const)

    if rank >= 8:
        return 8, "boss"

    if pool != "boss" and species_meta and species_meta.bst is not None:
        is_special = species_meta.is_legendary or species_meta.is_mythical or species_meta.is_ultra_beast
        if species_meta.is_frontier_banned:
            return 8, "boss"
        if (species_meta.is_legendary or species_meta.is_mythical) and species_meta.bst >= 660:
            return 8, "boss"
        if is_special and species_meta.bst >= 570:
            rank = max(rank, 5)
        elif species_meta.is_paradox and species_meta.bst >= 570:
            rank = max(rank, 5)
        elif species_meta.bst >= 600:
            rank = max(rank, 5)
        elif species_meta.bst >= 540:
            rank = max(rank, 4)

    return rank, pool


def explicit_rank(build: dict) -> int | None:
    if "rank" not in build:
        return None
    return max(0, min(8, int(build["rank"])))


def build_pool(build: dict) -> str:
    return build.get("pool") or build.get("frontier_pool") or "main"


def build_rank(build: dict, item_const: str) -> int:
    fmt = (build.get("format") or "").lower()
    pool = build_pool(build)
    tier = build.get("champions_tier")

    if pool == "boss":
        return 8
    if build.get("is_mega_set") or is_mega_stone_item(item_const):
        return 6
    if fmt in ("lc", "gen9lc"):
        return 0
    if "nfe" in fmt:
        return 1
    if "randombattle" in fmt or fmt == "frontier_missingmon_custom" or fmt in ("zu", "gen9zu", "pu", "gen9pu"):
        return 2
    if fmt in ("nu", "gen9nu", "ru", "gen9ru", "nationaldexru") or (fmt.startswith("pokemon_champions") and tier == "D"):
        return 3
    if fmt in ("uu", "gen9uu", "nationaldexuu") or (fmt.startswith("pokemon_champions") and tier == "C"):
        return 4
    if fmt.startswith("pokemon_champions") and tier in ("S", "A"):
        return 6
    return 5


def sanitize_frontier_mon_name(species_const: str) -> str:
    name = species_const.removeprefix("SPECIES_")
    name = re.sub(r"[^A-Z0-9_]", "_", name)
    name = re.sub(r"_+", "_", name).strip("_")
    return f"FRONTIER_MON_{name}"


def ev_tuple(build: dict) -> tuple[int, int, int, int, int, int]:
    evs = build.get("evs") or {}
    values = []
    for stat in STAT_ORDER:
        value = int(evs.get(stat, 0))
        value = max(0, min(252, value))
        values.append(value)
    return tuple(values)  # type: ignore[return-value]


def normalize_moves(build: dict) -> tuple[str, str, str, str]:
    moves = list(build.get("move_consts") or build.get("moves") or [])
    moves = [move for move in moves if move]
    moves = moves[:4]
    while len(moves) < 4:
        moves.append("MOVE_NONE")
    return tuple(moves)  # type: ignore[return-value]


def build_set_name(build: dict) -> str:
    return build.get("set_name") or build.get("name") or "Frontier Set"


def source_priority(build: dict | Entry) -> int:
    source = build.source if isinstance(build, Entry) else build.get("source", "")
    return SOURCE_PRIORITY.get(source, 99)


def dedupe_movepool_key(raw: dict) -> tuple[str, str, str, tuple[str, ...]]:
    form_key = raw["item_const"] if raw["is_mega_set"] else "regular"
    moves = tuple(sorted(move for move in raw["move_consts"] if move != "MOVE_NONE"))
    return raw["species_const"], raw["pool"], form_key, moves


def duplicate_preference_key(raw: dict) -> tuple:
    return (
        source_priority(raw),
        -raw["rank"],
        0 if raw["item_const"] != "ITEM_NONE" else 1,
        raw["set_name"],
        raw["item_const"],
        raw["ability_const"],
        raw["nature_const"],
        raw["evs"],
    )


def describe_deduped_entry(dropped: dict, kept: dict, moves: tuple[str, ...]) -> str:
    return (
        f"{dropped['species_name']} / {dropped['set_name']} ({dropped['source']}, {dropped['format_name']}) "
        f"duplicates {kept['species_name']} / {kept['set_name']} "
        f"with {', '.join(moves)}"
    )


def deduplicate_raw_entries(raw_entries: list[dict]) -> tuple[list[dict], list[str]]:
    kept_by_key: dict[tuple[str, str, str, tuple[str, ...]], dict] = {}
    deduped: list[str] = []

    for raw in raw_entries:
        key = dedupe_movepool_key(raw)
        kept = kept_by_key.get(key)
        if kept is None:
            kept_by_key[key] = raw
            continue

        if duplicate_preference_key(raw) < duplicate_preference_key(kept):
            kept_by_key[key] = raw
            deduped.append(describe_deduped_entry(kept, raw, key[3]))
        else:
            deduped.append(describe_deduped_entry(raw, kept, key[3]))

    return list(kept_by_key.values()), deduped


def load_entries(input_path: Path, constants: set[str], species_meta: dict[str, SpeciesMeta]) -> tuple[list[Entry], list[str], list[str]]:
    data = json.loads(input_path.read_text())
    raw_entries: list[dict] = []
    skipped: list[str] = []

    for species_name, mon in data["pokemon"].items():
        species_const = mon.get("species_const") or mon.get("species")
        for build in mon.get("sets") or mon.get("builds", []):
            item_const = build.get("item_const") or build.get("item") or "ITEM_NONE"
            ability_const = build.get("ability_const") or build.get("ability") or "ABILITY_NONE"
            nature_const = build.get("nature_const") or build.get("nature") or "NATURE_HARDY"
            move_consts = normalize_moves(build)
            meta = species_meta.get(species_const)
            rank, pool = adjusted_rank_and_pool(build, meta, item_const)

            tera_hits = tera_specific_hits(species_const, ability_const, move_consts)
            if tera_hits:
                skipped.append(f"{species_name} / {build_set_name(build)}: tera-specific {', '.join(tera_hits)}")
                continue

            missing = []
            if species_const not in constants:
                missing.append(species_const)
            if item_const not in constants:
                missing.append(item_const)
            if ability_const not in constants:
                missing.append(ability_const)
            if nature_const not in constants:
                missing.append(nature_const)
            missing.extend(move for move in move_consts if move not in constants)

            if missing:
                skipped.append(f"{species_name} / {build.get('set_name')}: missing {', '.join(sorted(set(missing)))}")
                continue

            raw_entries.append(
                {
                    "species_name": species_name,
                    "species_const": species_const,
                    "source_form": build.get("source_form") or build.get("form") or species_name,
                    "set_name": build_set_name(build),
                    "source": build.get("source") or "unknown",
                    "format_name": build.get("format") or "manual",
                    "rank": rank,
                    "pool": pool,
                    "move_consts": move_consts,
                    "item_const": item_const,
                    "ability_const": ability_const,
                    "nature_const": nature_const,
                    "evs": ev_tuple(build),
                    "types": meta.types if meta else frozenset(),
                    "is_mega_set": bool(build.get("is_mega_set") or build.get("mega")) or is_mega_stone_item(item_const),
                }
            )

    raw_entries, deduped = deduplicate_raw_entries(raw_entries)

    raw_entries.sort(
        key=lambda e: (
            e["rank"],
            e["species_const"],
            source_priority(e),
            e["set_name"],
            e["item_const"],
            e["move_consts"],
        )
    )

    per_species_count: collections.Counter[str] = collections.Counter()
    entries: list[Entry] = []
    for mon_id, raw in enumerate(raw_entries):
        base_name = sanitize_frontier_mon_name(raw["species_const"])
        per_species_count[raw["species_const"]] += 1
        const_name = f"{base_name}_{per_species_count[raw['species_const']]}"
        entries.append(Entry(mon_id=mon_id, const_name=const_name, **raw))

    return entries, skipped, deduped


def display_source_path(path: Path) -> str:
    try:
        return str(path.resolve().relative_to(ROOT))
    except ValueError:
        return str(path)


def write_constants(entries: list[Entry], source_name: str, path: Path) -> None:
    by_rank: dict[int, list[Entry]] = collections.defaultdict(list)
    for entry in entries:
        by_rank[entry.rank].append(entry)

    width = max(len(entry.const_name) for entry in entries)
    lines = [
        "#ifndef GUARD_CONSTANTS_BATTLE_FRONTIER_MONS_H",
        "#define GUARD_CONSTANTS_BATTLE_FRONTIER_MONS_H",
        "",
        "// Generated by tools/generate_battle_frontier_from_competitive_json.py.",
        f"// Source: {source_name}",
        "",
    ]
    for rank in sorted(r for r in by_rank if r != 8):
        lines.append(f"// Rank {rank}: {RANK_DESCRIPTIONS[rank]}")
        for entry in by_rank[rank]:
            lines.append(f"#define {entry.const_name:<{width}} {entry.mon_id}")
        lines.append("")

    if 8 in by_rank:
        lines.append("// Boss pool: Ubers/AG/high-power builds, open-level and Brain use only.")
        for entry in by_rank[8]:
            lines.append(f"#define {entry.const_name:<{width}} {entry.mon_id}")
        lines.append("")

    for rank in sorted(r for r in by_rank if r != 8):
        lines.append(f"#define FRONTIER_MON_RANK_{rank}_START {by_rank[rank][0].const_name}")
        lines.append(f"#define FRONTIER_MON_RANK_{rank}_END   {by_rank[rank][-1].const_name}")
    lines.append("")
    if 8 in by_rank:
        lines.append(f"#define FRONTIER_MON_BOSS_START {by_rank[8][0].const_name}")
        lines.append(f"#define FRONTIER_MON_BOSS_END   {by_rank[8][-1].const_name}")
        lines.append("#define FRONTIER_MONS_HIGH_TIER (FRONTIER_MON_BOSS_START - 1)")
    else:
        lines.append("#define FRONTIER_MONS_HIGH_TIER (NUM_FRONTIER_MONS - 1)")
    lines.append(f"#define NUM_FRONTIER_MONS       {len(entries)}")
    lines.append("")
    lines.append("#endif // GUARD_CONSTANTS_BATTLE_FRONTIER_MONS_H")
    lines.append("")
    path.write_text("\n".join(lines))


def write_mons(entries: list[Entry], path: Path) -> None:
    lines = [
        "// Generated by tools/generate_battle_frontier_from_competitive_json.py.",
        "const struct TrainerMon gBattleFrontierMons[NUM_FRONTIER_MONS] =",
        "{",
    ]
    for entry in entries:
        hp, atk, defense, speed, spatk, spdef = entry.evs
        lines.extend(
            [
                f"    [{entry.const_name}] = {{",
                f"        .species = {entry.species_const},",
                f"        .moves = {{{', '.join(entry.move_consts)}}},",
                f"        .heldItem = {entry.item_const},",
                f"        .ev = TRAINER_PARTY_EVS({hp}, {atk}, {defense}, {speed}, {spatk}, {spdef}),",
                f"        .nature = {entry.nature_const},",
            ]
        )
        if entry.ability_const != "ABILITY_NONE":
            lines.append(f"        .ability = {entry.ability_const},")
        lines.append("    },")
    lines.append("};")
    lines.append("")
    path.write_text("\n".join(lines))


def parse_macro_names(path: Path) -> list[str]:
    text = path.read_text()
    return re.findall(r"^#define\s+(FRONTIER_MONS_[A-Z0-9_]+)", text, re.M)


def parse_parameterized_macro_arities(path: Path) -> dict[str, int]:
    text = path.read_text()
    arities: dict[str, int] = {}
    for name, args in re.findall(r"(FRONTIER_MONS_[A-Z0-9_]+)\(([^)]*)\)", text):
        arity = len([arg for arg in args.split(",") if arg.strip()])
        arities[name] = max(arities.get(name, 0), arity)
    return arities


def macro_rank_window(name: str) -> set[int]:
    if name == "FRONTIER_MONS_EEVEELUTIONS":
        return {2, 3, 4, 5, 6}
    match = re.search(r"_(\d)([A-D])?(?:_|$)", name)
    if match:
        tier = int(match.group(1))
        letter = match.group(2)
        if tier <= 1:
            return {0, 1, 2}
        if tier == 2:
            return {4, 5, 6} if letter else {2, 3, 4}
        if tier == 3:
            return {3, 4, 5, 6}
        return {4, 5, 6}
    if name.endswith("_A"):
        return {4, 5, 6}
    if name.endswith("_B"):
        return {3, 4, 5, 6}
    if name.endswith("_C"):
        return {4, 5, 6}
    if name.endswith("_D"):
        return {5, 6}

    return {3, 4, 5}


def macro_theme_types(name: str) -> set[str]:
    if "SWIMMER" in name or "FISHERMAN" in name or "TUBER" in name or "SWIMMING_TRIATHLETE" in name:
        return TYPE_THEMES["WATER"]
    if "SAILOR" in name:
        return TYPE_THEMES["WATER"] | TYPE_THEMES["FIGHTING"]
    if "KINDLER" in name:
        return TYPE_THEMES["FIRE"]
    if "BIRD_KEEPER" in name:
        return TYPE_THEMES["FLYING"]
    if "BUG_CATCHER" in name or "BUG_MANIAC" in name:
        return TYPE_THEMES["BUG"]
    if "GUITARIST" in name:
        return TYPE_THEMES["ELECTRIC"] | TYPE_THEMES["STEEL"]
    if "BLACK_BELT" in name or "BATTLE_GIRL" in name:
        return TYPE_THEMES["FIGHTING"]
    if "PSYCHIC" in name:
        return TYPE_THEMES["PSYCHIC"]
    if "HEX_MANIAC" in name or "NINJA_BOY" in name:
        return TYPE_THEMES["GHOST_DARK"] | TYPE_THEMES["POISON"]
    if "DRAGON_TAMER" in name:
        return TYPE_THEMES["DRAGON"]
    if "HIKER" in name or "RUIN_MANIAC" in name:
        return TYPE_THEMES["ROCK_GROUND_STEEL"]
    if "AROMA_LADY" in name:
        return TYPE_THEMES["GRASS_FAIRY_POISON"]
    if "PARASOL_LADY" in name:
        return TYPE_THEMES["WATER"] | TYPE_THEMES["GRASS"] | TYPE_THEMES["ELECTRIC"]
    if "CAMPER_PICNICKER" in name:
        return TYPE_THEMES["OUTDOOR"]
    if "POKEFAN" in name or "BEAUTY" in name:
        return TYPE_THEMES["CUTE"]
    if "RICH_BOY_LADY" in name or "GENTLEMAN" in name or "COLLECTOR" in name:
        return TYPE_THEMES["RARE"] | TYPE_THEMES["CUTE"]
    if "POKEMANIAC" in name:
        return TYPE_THEMES["RARE"] | TYPE_THEMES["ROCK_GROUND_STEEL"]
    return set()


def macro_limit(name: str) -> int:
    if name == "FRONTIER_MONS_EEVEELUTIONS":
        return 96
    if "GENERAL" in name or "COOLTRAINER" in name or "EXPERT" in name or "PKMN_RANGER" in name:
        return 160
    if "YOUNGSTER_LASS" in name or "SCHOOL_KID" in name or "PKMN_BREEDER" in name:
        return 128
    return 96


def stable_rotate(entries: list[Entry], key: str) -> list[Entry]:
    if not entries:
        return entries
    digest = hashlib.sha256(key.encode("ascii")).hexdigest()
    offset = int(digest[:8], 16) % len(entries)
    return entries[offset:] + entries[:offset]


def select_macro_entries(name: str, entries: list[Entry]) -> list[Entry]:
    ranks = macro_rank_window(name)
    candidates = [entry for entry in entries if entry.pool == "main" and entry.rank in ranks]

    if name == "FRONTIER_MONS_EEVEELUTIONS":
        candidates = [entry for entry in candidates if entry.species_const in EEVEELUTION_SPECIES]
    else:
        theme_types = macro_theme_types(name)
        if theme_types:
            themed = [entry for entry in candidates if entry.types & theme_types]
            if len(themed) >= 24:
                candidates = themed

    if "NO_DUGTRIO" in name:
        candidates = [entry for entry in candidates if entry.species_const != "SPECIES_DUGTRIO"]

    if len(candidates) < 24:
        candidates = [entry for entry in entries if entry.pool == "main" and entry.rank in ranks]
    if len(candidates) < 24:
        candidates = [entry for entry in entries if entry.pool == "main"]

    candidates.sort(key=lambda e: (e.rank, e.species_const, source_priority(e), e.mon_id))
    candidates = stable_rotate(candidates, name)

    limit = macro_limit(name)
    selected: list[Entry] = []
    seen_species: set[str] = set()
    for entry in candidates:
        if entry.species_const in seen_species:
            continue
        selected.append(entry)
        seen_species.add(entry.species_const)
        if len(selected) >= limit:
            return selected

    for entry in candidates:
        if entry in selected:
            continue
        selected.append(entry)
        if len(selected) >= limit:
            break

    return selected


def write_trainer_mons(
    entries: list[Entry],
    macro_names: list[str],
    macro_arities: dict[str, int],
    path: Path,
) -> dict[str, int]:
    lines = [
        "// Generated by tools/generate_battle_frontier_from_competitive_json.py.",
        "// Historical FRONTIER_MONS_* macro names are kept so trainer scaling stays intact.",
        "",
    ]
    macro_sizes: dict[str, int] = {}
    for name in macro_names:
        selected = select_macro_entries(name, entries)
        macro_sizes[name] = len(selected)
        if name in macro_arities:
            params = ", ".join(f"arg{i}" for i in range(macro_arities[name]))
            lines.append(f"#define {name}({params}) \\")
        else:
            lines.append(f"#define {name} \\")
        for entry in selected:
            lines.append(f"    {entry.const_name}, \\")
        lines.append("    -1")
        lines.append("")
    path.write_text("\n".join(lines))
    return macro_sizes


def choose_brain_entry(entries_by_species: dict[str, list[Entry]], species_name: str, preferred_item: str | None, gold: bool) -> Entry:
    candidates = entries_by_species.get(species_name)
    if not candidates:
        raise ValueError(f"No build for Frontier Brain species {species_name}")

    if preferred_item:
        preferred = [entry for entry in candidates if entry.item_const == preferred_item]
        if preferred:
            candidates = preferred

    if gold:
        boss = [entry for entry in candidates if entry.pool == "boss"]
        if boss:
            candidates = boss
    else:
        main = [entry for entry in candidates if entry.pool == "main"]
        if main:
            candidates = main

    if not preferred_item:
        non_mega = [entry for entry in candidates if not entry.is_mega_set]
        if non_mega:
            candidates = non_mega

    candidates = sorted(
        candidates,
        key=lambda e: (
            0 if preferred_item and e.item_const == preferred_item else 1,
            0 if (gold and e.pool == "boss") else 1,
            -e.rank,
            source_priority(e),
            e.mon_id,
        ),
    )
    return candidates[0]


def write_brain_mons(entries: list[Entry], path: Path) -> list[str]:
    entries_by_species: dict[str, list[Entry]] = collections.defaultdict(list)
    for entry in entries:
        entries_by_species[entry.species_name].append(entry)

    report_lines: list[str] = []
    lines = [
        "// Generated by tools/generate_battle_frontier_from_competitive_json.py.",
        "static const struct FrontierBrainMon sFrontierBrainsMons[][2][FRONTIER_PARTY_SIZE] =",
        "{",
    ]

    for facility, teams in BRAIN_TEAMS.items():
        lines.append(f"    [FRONTIER_FACILITY_{facility}] =")
        lines.append("    {")
        for symbol, team in enumerate(teams):
            fixed_iv = BRAIN_SILVER_IVS[facility] if symbol == 0 else "MAX_PER_STAT_IVS"
            lines.append("        // Silver Symbol." if symbol == 0 else "        // Gold Symbol.")
            lines.append("        {")
            for species_name, preferred_item in team:
                entry = choose_brain_entry(entries_by_species, species_name, preferred_item, symbol == 1)
                hp, atk, defense, speed, spatk, spdef = entry.evs
                lines.extend(
                    [
                        "            {",
                        f"                .species = {entry.species_const},",
                        f"                .heldItem = {entry.item_const},",
                        f"                .fixedIV = {fixed_iv},",
                        f"                .nature = {entry.nature_const},",
                        f"                .evs = {{{hp}, {atk}, {defense}, {speed}, {spatk}, {spdef}}},",
                        f"                .moves = {{{', '.join(entry.move_consts)}}},",
                        "            },",
                    ]
                )
                report_lines.append(
                    f"{facility} {'Gold' if symbol else 'Silver'}: {entry.species_name} "
                    f"@ {entry.item_const} ({entry.source}, {entry.format_name}, {entry.set_name})"
                )
            lines.append("        },")
        lines.append("    },")
    lines.append("};")
    lines.append("")
    path.write_text("\n".join(lines))
    return report_lines


def replace_braced_initializer(path: Path, start_token: str, replacement: str) -> bool:
    text = path.read_text()
    if replacement.strip() in text:
        return True
    start = text.find(start_token)
    if start == -1:
        return False
    brace = text.find("{", start)
    if brace == -1:
        raise ValueError(f"Could not find initializer brace for {start_token}")
    depth = 0
    end = None
    for idx in range(brace, len(text)):
        char = text[idx]
        if char == "{":
            depth += 1
        elif char == "}":
            depth -= 1
            if depth == 0:
                semi = text.find(";", idx)
                if semi == -1:
                    raise ValueError(f"Could not find semicolon for {start_token}")
                end = semi + 1
                break
    if end is None:
        raise ValueError(f"Could not find end of initializer for {start_token}")
    path.write_text(text[:start] + replacement + text[end:])
    return True


def ensure_frontier_util_uses_generated_brains(root: Path) -> bool:
    include_line = '#include "data/battle_frontier/battle_frontier_brain_mons.h"\n'
    path = root / "src/frontier_util.c"
    return replace_braced_initializer(
        path,
        "static const struct FrontierBrainMon sFrontierBrainsMons",
        include_line,
    )


def ensure_factory_ranges_use_generated_ranks(root: Path) -> bool:
    replacement = """static const u16 sInitialRentalMonRanges[][2] =
{
    // Level 50: keep Factory progression inside the main Frontier pool.
    {FRONTIER_MON_RANK_2_START, FRONTIER_MON_RANK_3_END},
    {FRONTIER_MON_RANK_4_START, FRONTIER_MON_RANK_6_END},
    {FRONTIER_MON_RANK_5_START, FRONTIER_MON_RANK_6_END},
    {FRONTIER_MON_RANK_5_START, FRONTIER_MON_RANK_6_END},
    {FRONTIER_MON_RANK_6_START, FRONTIER_MONS_HIGH_TIER},
    {FRONTIER_MON_RANK_6_START, FRONTIER_MONS_HIGH_TIER},
    {FRONTIER_MON_RANK_6_START, FRONTIER_MONS_HIGH_TIER},
    {FRONTIER_MON_RANK_3_START, FRONTIER_MONS_HIGH_TIER},

    // Open level: late rounds may pull from the boss/high-power section.
    {FRONTIER_MON_RANK_4_START, FRONTIER_MON_RANK_5_END},
    {FRONTIER_MON_RANK_5_START, FRONTIER_MON_RANK_6_END},
    {FRONTIER_MON_RANK_5_START, FRONTIER_MONS_HIGH_TIER},
    {FRONTIER_MON_RANK_6_START, NUM_FRONTIER_MONS - 1},
    {FRONTIER_MON_RANK_5_START, NUM_FRONTIER_MONS - 1},
    {FRONTIER_MON_RANK_5_START, NUM_FRONTIER_MONS - 1},
    {FRONTIER_MON_RANK_5_START, NUM_FRONTIER_MONS - 1},
    {FRONTIER_MON_RANK_5_START, NUM_FRONTIER_MONS - 1},
};
"""
    path = root / "src/battle_factory.c"
    return replace_braced_initializer(path, "static const u16 sInitialRentalMonRanges[][2]", replacement)


def write_report(
    entries: list[Entry],
    source_name: str,
    skipped: list[str],
    deduped: list[str],
    macro_sizes: dict[str, int],
    brain_report: list[str],
    frontier_util_patched: bool,
    factory_patched: bool,
    path: Path,
) -> None:
    rank_counts = collections.Counter(entry.rank for entry in entries)
    species_by_rank: dict[int, set[str]] = collections.defaultdict(set)
    sources = collections.Counter(entry.source for entry in entries)
    for entry in entries:
        species_by_rank[entry.rank].add(entry.species_const)

    lines = [
        "Battle Frontier generation report",
        "=================================",
        "",
        f"Source JSON: {source_name}",
        f"Generated Frontier mons: {len(entries)}",
        f"Main-pool builds: {sum(1 for entry in entries if entry.pool == 'main')}",
        f"Boss-pool builds: {sum(1 for entry in entries if entry.pool == 'boss')}",
        f"Skipped invalid/filtered builds: {len(skipped)}",
        f"Deduplicated duplicate movepools: {len(deduped)}",
        "",
        "Rank counts:",
    ]
    for rank in sorted(rank_counts):
        label = "Boss pool" if rank == 8 else f"Rank {rank}"
        lines.append(f"- {label}: {rank_counts[rank]} builds / {len(species_by_rank[rank])} species")

    lines.extend(["", "Source counts:"])
    for source, count in sources.most_common():
        lines.append(f"- {source}: {count}")

    lines.extend(["", "Generated trainer macro sizes:"])
    for name, count in macro_sizes.items():
        lines.append(f"- {name}: {count}")

    lines.extend(["", "Frontier Brain teams:"])
    lines.extend(f"- {line}" for line in brain_report)

    lines.extend(
        [
            "",
            "Code integration:",
            f"- src/frontier_util.c brain table include patched: {frontier_util_patched}",
            f"- src/battle_factory.c Factory ranges patched: {factory_patched}",
        ]
    )

    if skipped:
        lines.extend(["", "Skipped invalid/filtered builds:"])
        lines.extend(f"- {line}" for line in skipped[:200])
        if len(skipped) > 200:
            lines.append(f"- ... {len(skipped) - 200} more")

    if deduped:
        lines.extend(["", "Deduplicated duplicate movepools:"])
        lines.extend(f"- {line}" for line in deduped[:200])
        if len(deduped) > 200:
            lines.append(f"- ... {len(deduped) - 200} more")

    lines.append("")
    path.write_text("\n".join(lines))


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("--input", type=Path, default=DEFAULT_INPUT)
    args = parser.parse_args()

    constants = collect_project_constants(ROOT)
    species_meta = parse_species_meta(ROOT)
    macro_names = parse_macro_names(TRAINER_MONS_OUT)
    macro_arities = parse_parameterized_macro_arities(TRAINERS_FILE)
    entries, skipped, deduped = load_entries(args.input, constants, species_meta)
    source_name = display_source_path(args.input)

    if not entries:
        raise SystemExit("No valid Frontier entries generated")
    if len(entries) > 0xFFFF:
        raise SystemExit("Too many Frontier entries for u16 mon IDs")

    write_constants(entries, source_name, CONSTANTS_OUT)
    write_mons(entries, MONS_OUT)
    macro_sizes = write_trainer_mons(entries, macro_names, macro_arities, TRAINER_MONS_OUT)
    brain_report = write_brain_mons(entries, BRAIN_MONS_OUT)
    frontier_util_patched = ensure_frontier_util_uses_generated_brains(ROOT)
    factory_patched = ensure_factory_ranges_use_generated_ranks(ROOT)
    write_report(entries, source_name, skipped, deduped, macro_sizes, brain_report, frontier_util_patched, factory_patched, REPORT_OUT)

    print(f"Generated {len(entries)} Frontier mons")
    print(f"Skipped/filtered {len(skipped)} builds")
    print(f"Deduplicated {len(deduped)} duplicate movepools")
    print(f"Wrote {CONSTANTS_OUT.relative_to(ROOT)}")
    print(f"Wrote {MONS_OUT.relative_to(ROOT)}")
    print(f"Wrote {TRAINER_MONS_OUT.relative_to(ROOT)}")
    print(f"Wrote {BRAIN_MONS_OUT.relative_to(ROOT)}")
    print(f"Wrote {REPORT_OUT.relative_to(ROOT)}")


if __name__ == "__main__":
    main()
