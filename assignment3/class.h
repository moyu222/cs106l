#include <string>
#include <cstddef>
#include <ostream>
#include <stdexcept>

class GameCharacter {
public:
    GameCharacter();
    GameCharacter(const std::string& name, int maxHp, size_t invCapacity);
    ~GameCharacter();

    // getter 均为 const
    std::string getName() const;
    int getHP() const;
    int getMaxHP() const;
    int getXP() const;
    size_t getLevel() const;
    size_t getInventorySize() const;
    size_t getInventoryCapacity() const;

    // setter
    void setName(const std::string& newName);
    void setMaxHP(int newMaxHP);
    void heal(int amount);
    void takeDamage(int amount);
    void addXP(int ammout);

    // 背包操作
    bool addItem(const std::string& item);
    std::string removeItem(size_t idx);
    const std::string& getItem(size_t idx) const;

    // 其他行为
    void attack(GameCharacter& target);
    bool operator==(const GameCharacter& rhs) const;

private:
    std::string name_;
    int hp_;
    int max_hp_;
    int xp_;
    size_t level_;

    std::string* inventory_;
    size_t inventory_capacity_;
    size_t inventory_size_;

    void ensureInventoryCapacity(size_t minCapacity);
    void clampHP();
    bool validInventoryIndex(size_t idx) const;
    void levelUpIfNeeded();
};