#include "class.h"

#include <algorithm>
#include <stdexcept>
#include <utility>
#include <cstring>

// constructor destructor
GameCharacter::GameCharacter()
    : name_{"Unnamed"},
      hp_{100},
      max_hp_{100},
      xp_{0},
      level_{1},
      inventory_{nullptr},
      inventory_capacity_{0},
      inventory_size_{0} {
        ensureInventoryCapacity(4);
}

GameCharacter::GameCharacter(const std::string& name, int maxHp, size_t invCapacity)
    : name_{name},
      hp_{std::max(0, maxHp)},
      max_hp_{100},
      xp_{0},
      level_{1},
      inventory_{nullptr},
      inventory_capacity_{0},
      inventory_size_{0} {
        ensureInventoryCapacity(std::max<size_t>(1, invCapacity));
        clampHP();
}

GameCharacter::~GameCharacter() {
    delete[] inventory_;
}

// getter
std::string GameCharacter::getName() const {
    return name_;
}

int GameCharacter::getHP() const {
    return hp_;
}

int GameCharacter::getMaxHP() const {
    return max_hp_;
}

int GameCharacter::getXP() const {
    return xp_;
}

size_t GameCharacter::getLevel() const {
    return level_;
}

size_t GameCharacter::getInventorySize() const {
    return inventory_size_;
}

size_t GameCharacter::getInventoryCapacity() const {
    return inventory_capacity_;
}

// setter
void GameCharacter::setName(const std::string& newName) {
    name_ = newName;
}

void GameCharacter::setMaxHP(int newMaxHP) {
    max_hp_ = std::max(1, newMaxHP);
    clampHP();
}

void GameCharacter::heal(int amount) {
    if (amount <= 0) return;
    hp_ += amount;
    clampHP();
}

void GameCharacter::takeDamage(int amount) {
    if (amount <= 0) return;
    hp_ -= amount;
    clampHP();
}

void GameCharacter::addXP(int amount) {
    if (amount <= 0) return;
    xp_ += amount;
    levelUpIfNeeded();
}

// 背包操作
bool GameCharacter::addItem(const std::string& item) {
    if (inventory_size_ >= inventory_capacity_) {
        // 扩容策略：至少翻倍
        size_t newCap = std::max<size_t>(1, inventory_capacity_ * 2);
        if (newCap <= inventory_capacity_) newCap = inventory_capacity_ + 1;
        ensureInventoryCapacity(newCap);
    }

    // 在下标 inventory_size_ 放入元素
    inventory_[inventory_size_] = item;
    ++inventory_size_;
    return true;
}

std::string GameCharacter::removeItem(size_t idx) {
    if (!validInventoryIndex(idx)) {
        throw std::out_of_range("removeItem: index out of range");
    }
    // 取出要删除的项
    std::string removed = std::move(inventory_[idx]);

    // 将后续项前移一位
    for (size_t i = idx + 1; i < inventory_size_; ++i) {
        inventory_[i - 1] = std::move(inventory_[i]);
    }
    --inventory_size_;
    // 可选：清空最后一项的字符串（保持干净）
    inventory_[inventory_size_].clear();
    return removed;
}

const std::string& GameCharacter::getItem(size_t idx) const {
    if (!validInventoryIndex(idx)) {
        throw std::out_of_range("getItem: index out of range");
    }
    return inventory_[idx];
}

void GameCharacter::attack(GameCharacter& target) {
    // 简单示例：伤害等于等级 * 5
    int damage = static_cast<int>(level_) * 5;
    target.takeDamage(damage);
    // 给予攻击者少量经验
    addXP(10);
}

bool GameCharacter::operator==(const GameCharacter& rhs) const {
    // 简单比较：名字相同且等级相同则认为相等
    return name_ == rhs.name_ && level_ == rhs.level_;
}

void GameCharacter::ensureInventoryCapacity(size_t minCapacity) {
    if (inventory_capacity_ >= minCapacity) return;

    size_t newCapacity = std::max(minCapacity, std::max<size_t>(1, inventory_capacity_ * 2));
    std::string* newArr = new std::string[newCapacity];

    // 拷贝现有元素（注意 inventory_size_ 可能为 0）
    for (size_t i = 0; i < inventory_size_; ++i) {
        newArr[i] = std::move(inventory_[i]);
    }

    // 释放旧数组并替换
    delete[] inventory_;
    inventory_ = newArr;
    inventory_capacity_ = newCapacity;
}

void GameCharacter::clampHP() {
    if (hp_ < 0) hp_ = 0;
    if (hp_ > max_hp_) hp_ = max_hp_;
}

bool GameCharacter::validInventoryIndex(size_t idx) const {
    return idx < inventory_size_;
}

void GameCharacter::levelUpIfNeeded() {
    // 简单经验规则：每 100 xp 升一级
    while (xp_ >= 100) {
        xp_ -= 100;
        ++level_;
        // 每升一级，增加 max_hp 并恢复部分生命
        max_hp_ += 10;
        hp_ = std::min(max_hp_, hp_ + 10);
    }
}