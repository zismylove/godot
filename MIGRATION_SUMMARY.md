# 4.2 -> 4.6 Migration Summary (Custom Engine Changes)

This document summarizes the custom engine features that were migrated from the 4.2 branch into the 4.6 codebase.

## Scope

Only engine-side changes were migrated. Editor modifications were intentionally excluded.

## Migrated Features

### 1) Custom 2D Engine Classes

The following custom 2D classes were added under `scene/2d/` and registered with the engine so they are available in scripts and the editor:

- `cAstar` (Node2D)
  - Lightweight Node2D wrapper class (empty shell in current form).
  - Purpose: placeholder or base for custom A* related logic at the scene level.

- `cTilemap` (Node2D)
  - Lightweight Node2D wrapper class (empty shell in current form).
  - Purpose: placeholder or base for custom TileMap logic at the scene level.

- `cPlaceItemNode` (Node2D)
  - Adds a `itemRes` Resource property.
  - Exposes `nat_setupPlaceItem(Dictionary)` as a GDVIRTUAL call (`setupPlaceItem`) to allow script-side overrides.
  - Purpose: generic node used to instantiate and configure placed items (e.g., trees) using a Resource reference.

- `cTileInfo` (Resource)
  - Simple Resource container with a `theID` string property.
  - Purpose: base resource for tile metadata.

- `cTreeTileinfo` (cTileInfo)
  - Adds tree placement parameters, a FastNoiseLite reference, resource path arrays, and weighted probability arrays.
  - `getRandomTreePath()` builds a weighted list of tree resources based on probabilities.
  - Purpose: data asset for tree generation (resources + probability distribution).

- `cLayerData` (Resource)
  - Holds layer generation settings (noise, threshold, terrain settings, atlas position, weight, add-on tile type).
  - Optional additive tile info via `cTileInfo`.
  - Purpose: data asset describing how a specific tile layer should be generated.

- `cSceneMake` (Node2D)
  - Multi-layer procedural terrain generator.
  - Supports base/second/third layers with independent noise frequency and continuity control.
  - Generates tiles on `TileMapLayer` nodes and optionally spawns trees using `cTreeTileinfo` data.
  - Exposes parameters for map size, thresholds, noise controls, random seed, and tree spacing.
  - Purpose: runtime or editor-time terrain generation with layered noise and optional tree placement.

- `cShadowMap` (TileMapLayer)
  - Tile-based shadow/visibility overlay with utilities to show/hide tiles in radial or custom patterns.
  - Supports simple circle-based reveal, custom ranges, and map initialization.
  - Purpose: fog-of-war or visibility mask system built on TileMapLayer.

#### Files Added

- `scene/2d/cAstar.h`
- `scene/2d/cAstar.cpp`
- `scene/2d/cTilemap.h`
- `scene/2d/cTilemap.cpp`
- `scene/2d/cPlaceItemNode.h`
- `scene/2d/cPlaceItemNode.cpp`
- `scene/2d/layerData.h`
- `scene/2d/layerData.cpp`
- `scene/2d/cSceneMake.h`
- `scene/2d/cSceneMake.cpp`
- `scene/2d/cShadowMap.h`
- `scene/2d/cShadowMap.cpp`

#### Registration

The classes are registered in `scene/register_scene_types.cpp` so they are discoverable by ClassDB and exposed for scripting and editor usage.

### 2) AStarGrid2D Connection Control API

`AStarGrid2D` was extended to support directional connection restrictions between points. This allows pathfinding to block movement from one point to another without marking the point as solid.

#### New Public API

- `set_point_connection_disabled(from_id, to_id, disabled = true)`
- `is_point_connection_disabled(from_id, to_id)`
- `clear_point_connections(id)`
- `clear_all_connections()`

#### Behavior

- The pathfinding neighbor expansion now checks the per-connection restriction map.
- If a connection is disabled, that edge is skipped when exploring neighbors.
- Calling `clear()` now also clears all connection restrictions.

#### Purpose

- Enables one-way or selective edge blocking.
- Useful for gates, doors, directional movement, or dynamic obstacles without changing cell solidity.

#### Files Modified

- `core/math/a_star_grid_2d.h`
- `core/math/a_star_grid_2d.cpp`

## Build Status

The engine builds successfully on Windows with VS2019 after these migrations.

## Excluded (Not Migrated)

- Editor-side modifications from 4.2 (explicitly skipped).
