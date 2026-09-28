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
DEFAULT_INPUT = ROOT / "src/data/battle_frontier_sets.party"
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
MAX_BUILDS_PER_SPECIES = 5
MAX_MEGA_BUILDS_PER_SPECIES = 2
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
        [("Lucario", "ITEM_LUCARIONITE"), ("Alakazam", None), ("Snorlax", None)],
        [("Lucario", "ITEM_LUCARIONITE_Z"), ("Entei", None), ("Raikou", None)],
    ],
    "DOME": [
        [("Chandelure", "ITEM_CHANDELURITE"), ("Swampert", None), ("Metagross", None)],
        [("Chandelure", "ITEM_CHANDELURITE"), ("Flutter Mane", None), ("Tapu Fini", None)],
    ],
    "PALACE": [
        [("Emboar", "ITEM-EMBOARITE"), ("Arcanine-Hisui", None), ("Milotic", None)],
        [("Emboar", "ITEM-EMBOARITE"), ("Kartana", None), ("Lugia", None)],
    ],
    "ARENA": [
        [("Heracross", "ITEM_HERACRONITE"), ("Kommo-o", None), ("Breloom", None)],
        [("Heracross", "ITEM_HERACRONITE"), ("Ho-Oh", None), ("Urshifu", None)],
    ],
    "FACTORY": [
        [("Kingambit", None), ("Garchomp", None), ("Pinsir", "ITEM_PINSIRITE")],
        [("Pinsir", "ITEM_PINSIRITE"), ("Solgaleo", None), ("Xurkitree", None)],
    ],
    "PIKE": [
        [("Seviper", None), ("Milotic", None), ("Glimmora", "ITEM_GLIMMORANITE")],
        [("Glimmora", "ITEM_GLIMMORANITE"), ("Naganadel", None), ("Yveltal", None)],
    ],
    "PYRAMID": [
        [("Golurk", "ITEM_GOLURKITE"), ("Cofagrigus", None), ("Regirock", None)],
        [("Regigigas", None), ("Golurk", "ITEM_GOLURKITE"), ("Regirock", None)],
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
    is_doubles_origin: bool


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


def strip_c_comments(text: str) -> str:
    return re.sub(r"/\*[\s\S]*?\*/", lambda match: "\n" * match.group(0).count("\n"), text)


def name_to_constant(value: str, prefix: str) -> str:
    value = value.strip()
    if value.upper().startswith(prefix):
        return value.upper()
    value = value.replace("♀", "_F").replace("♂", "_M")
    value = value.replace("'", "")
    value = re.sub(r"[^A-Za-z0-9]+", "_", value)
    value = re.sub(r"_+", "_", value).strip("_").upper()
    if value == "NONE":
        return f"{prefix}NONE"
    return f"{prefix}{value}"


def parse_party_evs(value: str, path: Path, line_num: int) -> dict[str, int]:
    stat_names = {
        "hp": "hp",
        "atk": "atk",
        "def": "def",
        "spe": "spe",
        "spa": "spa",
        "spd": "spd",
    }
    result: dict[str, int] = {}
    for part in value.split("/"):
        match = re.fullmatch(r"\s*(\d+)\s+(HP|Atk|Def|Spe|SpA|SpD)\s*", part, re.I)
        if not match:
            raise ValueError(f"{path}:{line_num}: invalid EV entry: {part.strip()}")
        amount = int(match.group(1))
        stat = stat_names[match.group(2).lower()]
        if amount > 252:
            raise ValueError(f"{path}:{line_num}: EV for {match.group(2)} exceeds 252")
        if stat in result:
            raise ValueError(f"{path}:{line_num}: duplicate EV stat {match.group(2)}")
        result[stat] = amount
    if sum(result.values()) > 510:
        raise ValueError(f"{path}:{line_num}: EV total exceeds 510")
    return result


def parse_party_pokemon_header(value: str) -> tuple[str, str]:
    if " @ " in value:
        pokemon_text, item_text = value.rsplit(" @ ", 1)
    else:
        pokemon_text, item_text = value, "None"

    pokemon_text = re.sub(r"\s+\([MF]\)$", "", pokemon_text.strip())
    nickname_match = re.fullmatch(r".+\(([^()]+)\)", pokemon_text)
    if nickname_match:
        pokemon_text = nickname_match.group(1)
    return name_to_constant(pokemon_text, "SPECIES_"), name_to_constant(item_text, "ITEM_")


def parse_frontier_set_block(
    group_name: str,
    set_id: str,
    body: str,
    path: Path,
    start_line: int,
) -> dict:
    lines = body.splitlines()
    index = 0
    metadata: dict[str, str] = {}
    allowed_metadata = {"Rank", "Style", "Source", "Set Name"}

    while index < len(lines):
        line = lines[index].strip()
        if not line:
            index += 1
            continue
        if ":" not in line:
            break
        key, value = (part.strip() for part in line.split(":", 1))
        if key not in allowed_metadata:
            break
        if key in metadata:
            raise ValueError(f"{path}:{start_line + index}: duplicate {key} field")
        metadata[key] = value
        index += 1

    if "Rank" not in metadata:
        raise ValueError(f"{path}:{start_line}: [{set_id}] is missing required Rank")
    try:
        rank = int(metadata["Rank"])
    except ValueError as error:
        raise ValueError(f"{path}:{start_line}: [{set_id}] has an invalid Rank") from error
    if rank not in set(range(7)) | {8}:
        raise ValueError(f"{path}:{start_line}: [{set_id}] Rank must be 0-6 or 8")

    style = metadata.get("Style", "General").lower()
    if style not in {"general", "singles", "doubles"}:
        raise ValueError(f"{path}:{start_line}: [{set_id}] Style must be General, Singles, or Doubles")

    while index < len(lines) and not lines[index].strip():
        index += 1
    if index >= len(lines):
        raise ValueError(f"{path}:{start_line}: [{set_id}] is missing its Pokemon")

    species_const, item_const = parse_party_pokemon_header(lines[index].strip())
    expected_species = name_to_constant(group_name, "SPECIES_")
    if species_const != expected_species:
        raise ValueError(
            f"{path}:{start_line + index}: [{set_id}] uses {species_const} "
            f"inside the {expected_species} group"
        )
    index += 1

    ability_const = "ABILITY_NONE"
    nature_const = "NATURE_HARDY"
    evs: dict[str, int] = {}
    moves: list[str] = []
    while index < len(lines):
        line = lines[index].strip()
        line_num = start_line + index
        index += 1
        if not line:
            continue
        if line.startswith("- "):
            moves.append(name_to_constant(line[2:], "MOVE_"))
            continue
        if line.endswith(" Nature") and ":" not in line:
            nature_const = name_to_constant(line.removesuffix(" Nature"), "NATURE_")
            continue
        if ":" not in line:
            raise ValueError(f"{path}:{line_num}: unknown Pokemon line: {line}")
        key, value = (part.strip() for part in line.split(":", 1))
        if key == "Ability":
            ability_const = name_to_constant(value, "ABILITY_")
        elif key == "EVs":
            evs = parse_party_evs(value, path, line_num)
        elif key == "Nature":
            nature_const = name_to_constant(value, "NATURE_")
        elif key in {"Level", "IVs"}:
            raise ValueError(f"{path}:{line_num}: {key} are controlled by the Battle Frontier")
        else:
            raise ValueError(f"{path}:{line_num}: unsupported Pokemon field: {key}")

    if not 1 <= len(moves) <= 4:
        raise ValueError(f"{path}:{start_line}: [{set_id}] must define between one and four moves")
    moves.extend(["MOVE_NONE"] * (4 - len(moves)))

    return {
        "set_id": set_id,
        "rank": rank,
        "pool": "boss" if rank == 8 else "main",
        "moves": moves,
        "item": item_const,
        "ability": ability_const,
        "nature": nature_const,
        "evs": evs,
        "name": metadata.get("Set Name", set_id),
        "source": metadata.get("Source", "Manual"),
        "format": "battle_frontier_party",
        "battle_style": "doubles_origin" if style == "doubles" else style,
    }


def parse_frontier_brains(body: str, path: Path, start_line: int) -> dict[str, list[str]]:
    matches = list(re.finditer(r"^\[([A-Z0-9_]+)\]\s*$", body, re.M))
    result: dict[str, list[str]] = {}
    expected = {f"{facility}_{symbol}" for facility in BRAIN_SILVER_IVS for symbol in ("SILVER", "GOLD")}

    for index, match in enumerate(matches):
        team_id = match.group(1)
        if team_id not in expected:
            raise ValueError(f"{path}:{start_line + body[:match.start()].count(chr(10))}: unknown Brain team [{team_id}]")
        section_end = matches[index + 1].start() if index + 1 < len(matches) else len(body)
        slots: dict[int, str] = {}
        for offset, raw_line in enumerate(body[match.end():section_end].splitlines(), 1):
            line = raw_line.strip()
            if not line:
                continue
            slot_match = re.fullmatch(r"([1-3]):\s*([A-Z0-9_]+)", line)
            if not slot_match:
                raise ValueError(f"{path}:{start_line + body[:match.end()].count(chr(10)) + offset}: invalid Brain slot")
            slots[int(slot_match.group(1))] = slot_match.group(2)
        if set(slots) != {1, 2, 3}:
            raise ValueError(f"{path}: Brain team [{team_id}] must define slots 1, 2, and 3")
        result[team_id] = [slots[slot] for slot in (1, 2, 3)]

    missing = expected - set(result)
    if missing:
        raise ValueError(f"{path}: missing Brain teams: {', '.join(sorted(missing))}")
    return result


def parse_party_source(path: Path) -> tuple[dict, dict[str, list[str]]]:
    text = strip_c_comments(path.read_text())
    group_matches = list(re.finditer(r"^====\s+([A-Z0-9_]+)\s+====\s*$", text, re.M))
    if not group_matches:
        raise ValueError(f"{path}: no ==== POKEMON ==== groups found")

    data = {"pokemon": {}}
    brain_teams: dict[str, list[str]] | None = None
    seen_set_ids: set[str] = set()
    for group_index, group_match in enumerate(group_matches):
        group_name = group_match.group(1)
        group_end = group_matches[group_index + 1].start() if group_index + 1 < len(group_matches) else len(text)
        body = text[group_match.end():group_end]
        body_line = text[:group_match.end()].count("\n") + 1
        if group_name == "FRONTIER_BRAINS":
            brain_teams = parse_frontier_brains(body, path, body_line)
            continue

        set_matches = list(re.finditer(r"^\[([A-Z0-9_]+)\]\s*$", body, re.M))
        if not set_matches:
            raise ValueError(f"{path}:{body_line}: [{group_name}] has no sets")
        species_const = name_to_constant(group_name, "SPECIES_")
        pokemon = data["pokemon"].setdefault(group_name, {"species_const": species_const, "sets": []})
        for set_index, set_match in enumerate(set_matches):
            set_id = set_match.group(1)
            if set_id in seen_set_ids:
                raise ValueError(f"{path}: duplicate set ID [{set_id}]")
            seen_set_ids.add(set_id)
            set_end = set_matches[set_index + 1].start() if set_index + 1 < len(set_matches) else len(body)
            set_body = body[set_match.end():set_end]
            set_line = body_line + body[:set_match.start()].count("\n") + 1
            pokemon["sets"].append(parse_frontier_set_block(group_name, set_id, set_body, path, set_line))

    if brain_teams is None:
        raise ValueError(f"{path}: missing ==== FRONTIER_BRAINS ==== section")
    return data, brain_teams


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


def retention_quality_key(raw: dict) -> tuple:
    return (
        -raw["rank"],
        source_priority(raw),
        0 if raw["item_const"] != "ITEM_NONE" else 1,
        raw["set_name"],
        raw["item_const"],
        raw["move_consts"],
    )


def move_overlap(left: dict, right: dict) -> int:
    left_moves = {move for move in left["move_consts"] if move != "MOVE_NONE"}
    right_moves = {move for move in right["move_consts"] if move != "MOVE_NONE"}
    return len(left_moves & right_moves)


def cap_builds_per_species(raw_entries: list[dict]) -> tuple[list[dict], list[str]]:
    by_species: dict[str, list[dict]] = collections.defaultdict(list)
    for raw in raw_entries:
        by_species[raw["species_const"]].append(raw)

    kept: list[dict] = []
    removed: list[str] = []
    for species_entries in by_species.values():
        if len(species_entries) <= MAX_BUILDS_PER_SPECIES:
            kept.extend(species_entries)
            continue

        megas = sorted((raw for raw in species_entries if raw["is_mega_set"]), key=retention_quality_key)
        selected: list[dict] = []
        selected_mega_items: set[str] = set()
        for raw in megas:
            if raw["item_const"] in selected_mega_items:
                continue
            selected.append(raw)
            selected_mega_items.add(raw["item_const"])
            if len(selected) == MAX_MEGA_BUILDS_PER_SPECIES:
                break
        for raw in megas:
            if len(selected) == MAX_MEGA_BUILDS_PER_SPECIES:
                break
            if raw not in selected:
                selected.append(raw)

        # Excess Mega builds are intentionally cut so regular variants keep room.
        remaining = [raw for raw in species_entries if not raw["is_mega_set"]]

        # Keep regular builds available in both normal and high-power play when possible.
        for pool in ("main", "boss"):
            if len(selected) >= MAX_BUILDS_PER_SPECIES:
                continue
            pool_entries = [raw for raw in remaining if raw["pool"] == pool]
            if pool_entries:
                choice = min(pool_entries, key=retention_quality_key)
                selected.append(choice)
                remaining.remove(choice)

        while len(selected) < MAX_BUILDS_PER_SPECIES and remaining:
            # Rank/source quality comes first; overlap breaks ties in favor of real variation.
            choice = min(
                remaining,
                key=lambda raw: (
                    -raw["rank"],
                    max((move_overlap(raw, other) for other in selected), default=0),
                    source_priority(raw),
                    0 if raw["item_const"] != "ITEM_NONE" else 1,
                    raw["set_name"],
                ),
            )
            selected.append(choice)
            remaining.remove(choice)

        kept.extend(selected)
        selected_ids = {id(raw) for raw in selected}
        for raw in species_entries:
            if id(raw) not in selected_ids:
                removed.append(
                    f"{raw['species_name']} / {raw['set_name']} "
                    f"({raw['source']}, {raw['format_name']}, rank {raw['rank']})"
                )

    return kept, removed


def load_entries(input_path: Path, constants: set[str], species_meta: dict[str, SpeciesMeta]) -> tuple[list[Entry], list[str], list[str], list[str], dict[str, list[str]] | None]:
    is_party_source = input_path.suffix == ".party"
    if is_party_source:
        data, brain_teams = parse_party_source(input_path)
    else:
        data = json.loads(input_path.read_text())
        brain_teams = None
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
                    "set_id": build.get("set_id"),
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
                    "is_doubles_origin": (
                        build.get("battle_style") == "doubles_origin"
                        or build.get("source") == "pokemon_champions"
                        or "vgc" in (build.get("format") or "").lower()
                    ),
                }
            )

    if is_party_source and skipped:
        raise ValueError(f"{input_path}: invalid Frontier set: {skipped[0]}")

    if is_party_source:
        # The .party file is the canonical, explicitly curated source. Preserve every
        # authored set; caps and movepool deduplication only belong to JSON imports.
        deduped = []
        capped = []
    else:
        raw_entries, deduped = deduplicate_raw_entries(raw_entries)
        raw_entries, capped = cap_builds_per_species(raw_entries)

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
    used_const_names: set[str] = set()
    entries: list[Entry] = []
    for mon_id, raw in enumerate(raw_entries):
        base_name = sanitize_frontier_mon_name(raw["species_const"])
        if raw["set_id"]:
            const_name = f"FRONTIER_MON_{raw['set_id']}"
        else:
            per_species_count[raw["species_const"]] += 1
            const_name = f"{base_name}_{per_species_count[raw['species_const']]}"
        if const_name in used_const_names:
            raise ValueError(f"Duplicate Frontier constant {const_name}")
        used_const_names.add(const_name)
        del raw["set_id"]
        entries.append(Entry(mon_id=mon_id, const_name=const_name, **raw))

    if brain_teams:
        available_ids = {entry.const_name.removeprefix("FRONTIER_MON_") for entry in entries}
        for team_id, set_ids in brain_teams.items():
            for set_id in set_ids:
                if set_id not in available_ids:
                    raise ValueError(f"Brain team [{team_id}] references unknown or removed set [{set_id}]")

    return entries, skipped, deduped, capped, brain_teams


def display_source_path(path: Path) -> str:
    try:
        return str(path.resolve().relative_to(ROOT))
    except ValueError:
        return str(path)


def sanitize_set_id_part(value: str) -> str:
    value = re.sub(r"[^A-Z0-9]+", "_", value.upper())
    return re.sub(r"_+", "_", value).strip("_")


def display_constant(value: str, prefix: str) -> str:
    value = value.removeprefix(prefix)
    return " ".join(part.capitalize() for part in value.split("_"))


def build_party_set_ids(entries: list[Entry]) -> dict[Entry, str]:
    result: dict[Entry, str] = {}
    used: set[str] = set()

    for entry in entries:
        species = entry.species_const.removeprefix("SPECIES_")
        if entry.is_mega_set:
            role = "MEGA_Z" if entry.item_const.endswith("ITE_Z") else "MEGA"
        elif entry.is_doubles_origin:
            item = entry.item_const.removeprefix("ITEM_")
            role = f"VGC_{item}" if item != "NONE" else "VGC"
        else:
            role = sanitize_set_id_part(entry.set_name) or entry.item_const.removeprefix("ITEM_") or "SET"

        base = sanitize_set_id_part(f"{species}_{role}")
        set_id = base
        if set_id in used:
            item = entry.item_const.removeprefix("ITEM_")
            if item != "NONE" and not set_id.endswith(item):
                set_id = sanitize_set_id_part(f"{base}_{item}")
        suffix = 2
        unique_id = set_id
        while unique_id in used:
            unique_id = f"{set_id}_{suffix}"
            suffix += 1
        used.add(unique_id)
        result[entry] = unique_id

    return result


def format_party_evs(evs: tuple[int, int, int, int, int, int]) -> str:
    labels = ("HP", "Atk", "Def", "Spe", "SpA", "SpD")
    values = [f"{value} {label}" for value, label in zip(evs, labels) if value]
    return " / ".join(values) if values else "0 HP"


def write_party_source(entries: list[Entry], path: Path) -> None:
    set_ids = build_party_set_ids(entries)
    lines = [
        "/*",
        "Battle Frontier Pokemon sets",
        "================================",
        "",
        "This is the editable source for every Battle Frontier set.",
        "The syntax follows Pokemon Showdown exports with a small Frontier header.",
        "",
        "A Pokemon group starts with:",
        "    ==== GARCHOMP ====",
        "",
        "Each build below it starts with a globally unique ID:",
        "    [GARCHOMP_VGC_LIFE_ORB]",
        "",
        "Required Frontier field:",
        "    Rank: 0 through 6, or 8 for the boss/high-power pool.",
        "",
        "Rank strength bands:",
        "    Rank 0: LC and other very weak introductory builds.",
        "    Rank 1: NFE builds.",
        "    Rank 2: ZU, PU, random-battle, and missing-mon builds.",
        "    Rank 3: NU, RU, National Dex RU, and Champions D builds.",
        "    Rank 4: UU, National Dex UU, and Champions C builds.",
        "    Rank 5: OU, Battle Stadium, National Dex, and Champions B builds.",
        "    Rank 6: main-pool Mega and Champions S/A builds.",
        "    Rank 8: Ubers, AG, and other boss/high-power builds.",
        "",
        "Normal themed-trainer progression:",
        "    Rank is a strength band, not an exact minimum streak. The selected trainer",
        "    first determines a themed set pool; one Pokemon is then drawn from that pool.",
        "    Facilities advance an internal challenge index using their native run format.",
        "",
        "    Challenge index 0: ordinary trainers use R0-2; the hard/final pick uses R2-4.",
        "    Challenge index 1: ordinary trainers may use R2-6; hard/final uses R3-6.",
        "    Challenge index 2 and later: trainers usually use R3-6.",
        "",
        "    In a seven-battle format such as the Tower, index 1 starts at streak 7,",
        "    so Rank 6 and Mega builds can appear from battle 8 onward. Dome, Pike,",
        "    and Pyramid advance through tournaments, rooms, or floors instead.",
        "    Individual trainers still keep their type/theme and narrower rank window.",
        "    Rank 8 is never placed in a normal trainer pool, even in Open Level.",
        "",
        "Battle Factory direct rank ranges:",
        "    Factory Pokemon are drawn directly by challenge number, without trainer themes.",
        "    Level 50: 0-6 wins R2-3; 7-13 R4-6; 14-27 R5-6;",
        "              28-48 R6; 49+ R3-6.",
        "    Open Level: 0-6 wins R4-5; 7-13 R5-6; 14-20 R5-6;",
        "                21-27 R6-8; 28+ R5-8.",
        "    Rental progression can improve some draft slots to the next range one",
        "    challenge earlier. Level 50 always excludes Rank 8.",
        "",
        "Frontier Brains:",
        "    Brain teams reference exact set IDs in ==== FRONTIER_BRAINS ====.",
        "    Their referenced sets are used regardless of Rank; Rank only describes power",
        "    and controls availability outside that explicit Brain team.",
        "",
        "Optional Frontier fields:",
        "    Style: General, Singles, or Doubles. Defaults to General.",
        "    Source: Informational origin of the set. Defaults to Manual.",
        "    Set Name: Human-readable label. Defaults to the set ID.",
        "",
        "Pokemon use normal Showdown fields:",
        "    Pokemon @ Item",
        "    Ability: Ability Name",
        "    EVs: 252 HP / 252 Atk / 4 Spe",
        "    Nature: Adamant",
        "    - Move One",
        "    - Move Two",
        "    - Move Three",
        "    - Move Four",
        "",
        "Notes:",
        "    - Species, item, ability, nature, and moves may also use project constants.",
        "    - Level and IVs are controlled by the Frontier and should not be specified.",
        "    - Rank 8 is excluded from Level 50 and all normal trainer pools.",
        "    - The initial set selection was curated to roughly five builds per species.",
        "    - This is not a parser limit; manually added regular or Mega sets are preserved.",
        "    - Tera-specific species, abilities, and moves are rejected.",
        "    - Style: Doubles enables the flexible VGC weighting in double/multi battles.",
        "",
        "Frontier Brain teams are listed at the end under ==== FRONTIER_BRAINS ====.",
        "Each slot references one set ID, so Brain sets are never duplicated.",
        "*/",
        "",
    ]

    by_species: dict[str, list[Entry]] = collections.defaultdict(list)
    for entry in entries:
        by_species[entry.species_const].append(entry)

    for species_const in sorted(by_species):
        lines.append(f"==== {species_const.removeprefix('SPECIES_')} ====")
        lines.append("")
        for entry in sorted(by_species[species_const], key=lambda item: (item.rank, set_ids[item])):
            lines.append(f"[{set_ids[entry]}]")
            lines.append(f"Rank: {entry.rank}")
            lines.append(f"Style: {'Doubles' if entry.is_doubles_origin else 'Singles'}")
            lines.append(f"Source: {entry.source}")
            lines.append(f"Set Name: {entry.set_name}")
            lines.append("")
            species_name = display_constant(entry.species_const, "SPECIES_")
            item_name = display_constant(entry.item_const, "ITEM_")
            header = species_name if entry.item_const == "ITEM_NONE" else f"{species_name} @ {item_name}"
            lines.append(header)
            if entry.ability_const != "ABILITY_NONE":
                lines.append(f"Ability: {display_constant(entry.ability_const, 'ABILITY_')}")
            lines.append(f"EVs: {format_party_evs(entry.evs)}")
            lines.append(f"Nature: {display_constant(entry.nature_const, 'NATURE_')}")
            for move in entry.move_consts:
                if move != "MOVE_NONE":
                    lines.append(f"- {display_constant(move, 'MOVE_')}")
            lines.append("")
        lines.append("")

    lines.append("==== FRONTIER_BRAINS ====")
    lines.append("")
    entries_by_species: dict[str, list[Entry]] = collections.defaultdict(list)
    for entry in entries:
        entries_by_species[entry.species_name].append(entry)
    for facility, teams in BRAIN_TEAMS.items():
        for symbol, team in enumerate(teams):
            lines.append(f"[{facility}_{'GOLD' if symbol else 'SILVER'}]")
            for slot, (species_name, preferred_item) in enumerate(team, 1):
                entry = choose_brain_entry(entries_by_species, species_name, preferred_item, symbol == 1)
                lines.append(f"{slot}: {set_ids[entry]}")
            lines.append("")

    path.write_text("\n".join(lines))


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
    lines.append("#define FRONTIER_MON_FLAG_DOUBLES_ORIGIN (1 << 0)")
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
    lines.extend(
        [
            "const u8 gBattleFrontierMonFlags[NUM_FRONTIER_MONS] =",
            "{",
        ]
    )
    for entry in entries:
        if entry.is_doubles_origin:
            lines.append(f"    [{entry.const_name}] = FRONTIER_MON_FLAG_DOUBLES_ORIGIN,")
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


def write_brain_mons(
    entries: list[Entry],
    path: Path,
    brain_set_ids: dict[str, list[str]] | None = None,
) -> list[str]:
    entries_by_species: dict[str, list[Entry]] = collections.defaultdict(list)
    for entry in entries:
        entries_by_species[entry.species_name].append(entry)
    entries_by_id = {
        entry.const_name.removeprefix("FRONTIER_MON_"): entry
        for entry in entries
    }

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
            if brain_set_ids is not None:
                team_id = f"{facility}_{'GOLD' if symbol else 'SILVER'}"
                selected_entries = [entries_by_id[set_id] for set_id in brain_set_ids[team_id]]
            else:
                selected_entries = [
                    choose_brain_entry(entries_by_species, species_name, preferred_item, symbol == 1)
                    for species_name, preferred_item in team
                ]
            lines.append("        // Silver Symbol." if symbol == 0 else "        // Gold Symbol.")
            lines.append("        {")
            for entry in selected_entries:
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
    capped: list[str],
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
        f"Removed by {MAX_BUILDS_PER_SPECIES}-build species cap: {len(capped)}",
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

    if capped:
        lines.extend(["", f"Removed by {MAX_BUILDS_PER_SPECIES}-build species cap:"])
        lines.extend(f"- {line}" for line in capped[:200])
        if len(capped) > 200:
            lines.append(f"- ... {len(capped) - 200} more")

    lines.append("")
    path.write_text("\n".join(lines))


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("--input", type=Path, default=DEFAULT_INPUT)
    parser.add_argument("--export-party", type=Path)
    args = parser.parse_args()

    constants = collect_project_constants(ROOT)
    species_meta = parse_species_meta(ROOT)
    macro_names = parse_macro_names(TRAINER_MONS_OUT)
    macro_arities = parse_parameterized_macro_arities(TRAINERS_FILE)
    entries, skipped, deduped, capped, brain_set_ids = load_entries(args.input, constants, species_meta)
    source_name = display_source_path(args.input)

    if args.export_party:
        write_party_source(entries, args.export_party)
        print(f"Wrote {display_source_path(args.export_party)}")
        return

    if not entries:
        raise SystemExit("No valid Frontier entries generated")
    if len(entries) > 0xFFFF:
        raise SystemExit("Too many Frontier entries for u16 mon IDs")

    write_constants(entries, source_name, CONSTANTS_OUT)
    write_mons(entries, MONS_OUT)
    macro_sizes = write_trainer_mons(entries, macro_names, macro_arities, TRAINER_MONS_OUT)
    brain_report = write_brain_mons(entries, BRAIN_MONS_OUT, brain_set_ids)
    frontier_util_patched = ensure_frontier_util_uses_generated_brains(ROOT)
    factory_patched = ensure_factory_ranges_use_generated_ranks(ROOT)
    write_report(entries, source_name, skipped, deduped, capped, macro_sizes, brain_report, frontier_util_patched, factory_patched, REPORT_OUT)

    print(f"Generated {len(entries)} Frontier mons")
    print(f"Skipped/filtered {len(skipped)} builds")
    print(f"Deduplicated {len(deduped)} duplicate movepools")
    print(f"Removed {len(capped)} builds above the per-species cap")
    print(f"Wrote {CONSTANTS_OUT.relative_to(ROOT)}")
    print(f"Wrote {MONS_OUT.relative_to(ROOT)}")
    print(f"Wrote {TRAINER_MONS_OUT.relative_to(ROOT)}")
    print(f"Wrote {BRAIN_MONS_OUT.relative_to(ROOT)}")
    print(f"Wrote {REPORT_OUT.relative_to(ROOT)}")


if __name__ == "__main__":
    main()
