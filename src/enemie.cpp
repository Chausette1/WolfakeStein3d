#include "enemie.hpp"

namespace {

std::vector<Vector2>
_BFS(std::set<Vector2> visited_positions,
     std::vector<Vector2> queue,
     Vector2 target_pos,
     map_t& map)
{
    const std::vector<Vector2> directions = { { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 } };
    std::map<Vector2, Vector2> parent;

    Vector2 buff = { floor(queue[0].x), floor(queue[0].y) };
    parent[buff] = { -1, -1 };
    visited_positions.insert(buff);

    target_pos.x = static_cast<int>(target_pos.x);
    target_pos.y = static_cast<int>(target_pos.y);

    while (!queue.empty()) {
        Vector2 current_pos = queue.front();
        queue.erase(queue.begin());

        current_pos.x = static_cast<int>(current_pos.x);
        current_pos.y = static_cast<int>(current_pos.y);

        if (current_pos.x == target_pos.x && current_pos.y == target_pos.y) {
            std::vector<Vector2> path;

            while (parent[current_pos] != Vector2{ -1, -1 }) {
                //!= parent.end() means found
                path.push_back(current_pos);
                current_pos = parent[current_pos];
            }
            std::reverse(path.begin(), path.end());
            return path;
        }

        for (const auto& dir : directions) {
            Vector2 neighbor_pos = { current_pos.x + dir.x, current_pos.y + dir.y };

            if (neighbor_pos.x < 0 || neighbor_pos.x >= map.width || neighbor_pos.y < 0 ||
                neighbor_pos.y >= map.height) {
                continue;
            }

            MapTile tile =
              map.data[static_cast<int>(neighbor_pos.y)][static_cast<int>(neighbor_pos.x)];

            if (tile != MapTile::Empty) {
                continue;
            }

            if (visited_positions.find(neighbor_pos) == visited_positions.end()) {
                // == visited_positions.end() means not found
                visited_positions.insert(neighbor_pos);
                queue.push_back(neighbor_pos);
                parent[neighbor_pos] = current_pos;
            }
        }
    }
    throw std::runtime_error("Path to player not found");
}

}

Enemie::Enemie(Vector2 pos, int texture_id, map_t& map, int id, Vector2 player_pos)
  : map(&map)
  , speed(ENEMIE_STEP)
  , position(pos)
  , texture_id(texture_id)
  , id(id)
{
    this->map->sprites.push_back(new sprite_t{ pos, SpriteType::Enemy, true, id });

    this->path_to_player = _BFS(std::set<Vector2>(), { this->position }, player_pos, map);

    last_distance_to_player =
      sqrt(pow(player_pos.x - position.x, 2) + pow(player_pos.y - position.y, 2));

    this->update_texture_in_map();
};

Enemie::~Enemie()
{
    this->map = nullptr;
}

void
Enemie::update_texture_in_map()
{
    int map_x = static_cast<int>(this->position.x);
    int map_y = static_cast<int>(this->position.y);

    if (map_x >= 0 && map_x < this->map->width && map_y >= 0 && map_y < this->map->height) {
        // not implemented yet
        for (auto& sprite : this->map->sprites) {
            if (sprite->id == this->id) {
                sprite->position = this->position;
                sprite->texture_id = this->texture_id;
                break;
            }
        }
    }
}

void
Enemie::move_toward_player(Player* player, map_t& map)
{
    Vector2 player_pos = { player->get_x() / MINI_MAP_TILE_SIZE,
                           player->get_y() / MINI_MAP_TILE_SIZE };

    float distance_to_player =
      sqrt(pow(player_pos.x - this->position.x, 2) + pow(player_pos.y - this->position.y, 2));

    if (last_distance_to_player > distance_to_player || path_to_player.empty()) {
        // player is closer, recalculate path
        path_to_player.clear();
        path_to_player = _BFS(std::set<Vector2>(), { this->position }, player_pos, map);
    }

    std::vector<Vector2> new_end_of_path;
    if (path_to_player.empty()) {
        return;
    }
    new_end_of_path.push_back(path_to_player.back());

    new_end_of_path = _BFS(std::set<Vector2>(), new_end_of_path, player_pos, map);

    if (new_end_of_path.size() > 1) {

        new_end_of_path.erase(new_end_of_path.begin());

        // add new_end_of_path to path_to_player
        for (const auto& pos : new_end_of_path) {
            path_to_player.push_back(pos);
        }
    }
    // }

    last_distance_to_player = distance_to_player;
    Vector2 dir = { (path_to_player[0].x + 0.5f) - this->position.x,
                    (path_to_player[0].y + 0.5f) - this->position.y };

    if (abs(dir.x) > 0.1f) {
        dir.x = dir.x / abs(dir.x);
    } else {
        dir.x = 0;
    }
    if (abs(dir.y) > 0.1f) {
        dir.y = dir.y / abs(dir.y);
    } else {
        dir.y = 0;
    }

    this->position.x += dir.x * this->speed;
    this->position.y += dir.y * this->speed;

    if (abs(this->position.x - (path_to_player[0].x + 0.5f)) < 0.1f &&
        abs(this->position.y - (path_to_player[0].y + 0.5f)) < 0.1f && path_to_player.size() > 0) {
        path_to_player.erase(path_to_player.begin());
    }

    this->update_texture_in_map();
}

bool
Enemie::can_attack(Player* player) const
{
    Vector2 player_pos = { player->get_x() / MINI_MAP_TILE_SIZE,
                           player->get_y() / MINI_MAP_TILE_SIZE };

    float distance_to_player =
      sqrt(pow(player_pos.x - this->position.x, 2) + pow(player_pos.y - this->position.y, 2));

    return distance_to_player < 0.7f && !this->attacking;
}

void
Enemie::attack()
{
    this->attacking = true;
    this->attack_tick = 0;
}

bool
Enemie::is_attacking() const
{
    return this->attacking;
}

void
Enemie::update_attack_animation(Player* player)
{
    if (this->enemie_life <= 0) {
        return;
    }
    switch (attack_tick) {
        case 1:
            this->texture_id = 1;
            this->update_texture_in_map();
            break;
        case 6:
            player->take_damage(this->enemie_damage);
            break;
        case 13:
            this->attacking = false;
            this->texture_id = 0;
            this->attack_tick = 0;
            this->update_texture_in_map();
            return;
        default:
            break;
    }
    this->attack_tick++;
}

void
Enemie::take_damage(int damage)
{
    if (this->enemie_life <= 0) {
        return;
    }
    this->enemie_life -= damage;
    if (this->enemie_life <= 0) {
        for (auto it = this->map->sprites.begin(); it != this->map->sprites.end(); ++it) {
            if ((*it)->id == this->id) {
                delete *it;
                this->map->sprites.erase(it);
                break;
            }
        }
    }
}
