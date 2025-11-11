#include "game_object.h"

GameObject::GameObject()
    : Position(0.0f, 0.0f), Color(1.0f, 1.0f, 1.0f), Sprite() {}

GameObject::GameObject(glm::vec2 pos, Texture &sprite, glm::vec2 size,
                       float rotation, glm::vec3 color)
    : Position(pos), Sprite(sprite), Color(color) {}

void GameObject::Draw(SpriteRenderer &renderer) {
  renderer.DrawSprite(this->Sprite, this->Position, this->Size, this->Rotation, this->Color);
}
