/*
 * CS106L Assignment 3: Make a Class
 * Created by Fabio Ibanez with modifications by Jacob Roberts-Baca.
 */

// sandbox.cpp
#include "class.h"
#include <iostream>

void printStatus(const GameCharacter& c, const char* tag) {
    std::cout << "[" << tag << "] "
              << "Name: " << c.getName()
              << ", Level: " << c.getLevel()
              << ", HP: " << c.getHP() << "/" << c.getMaxHP()
              << ", XP: " << c.getXP()
              << ", Inventory: " << c.getInventorySize() << "/" << c.getInventoryCapacity()
              << "\n";
}

void sandbox() {
    // 1. 默认构造角色
    GameCharacter wanderer;
    wanderer.setName("Wanderer");
    wanderer.addItem("Apple");
    wanderer.addItem("Rope");

    // 2. 有参构造主角
    GameCharacter hero("Arin", 140, 4);
    hero.addItem("Health Potion");
    hero.addItem("Short Sword");

    // 3. 有参构造敌人
    GameCharacter bandit("Bandit", 75, 3);
    bandit.addItem("Dagger");
    bandit.addItem("Coin");

    // 打印初始状态
    printStatus(wanderer, "Wanderer");
    printStatus(hero, "Hero");
    printStatus(bandit, "Bandit");

    // 4. 简单战斗回合：hero 攻击 bandit，两者交换动作
    hero.attack(bandit);
    bandit.attack(hero);

    // 5. hero 使用回复药水并获得经验以触发升级逻辑
    hero.heal(25);
    hero.addXP(110); // 超过 100，触发一次或多次升级

    // 6. 背包操作：移除合法索引的物品并展示
    if (wanderer.getInventorySize() > 0) {
        std::string removed = wanderer.removeItem(0); // 移除第一个物品
        std::cout << "Wanderer removed: " << removed << "\n";
    }

    // 7. 再次打印最终状态以验证所有基本操作
    printStatus(wanderer, "Wanderer final");
    printStatus(hero, "Hero final");
    printStatus(bandit, "Bandit final");

    // 8. 使用返回值避免编译器优化掉未使用的变量
    (void)hero.getName();
    (void)bandit.getHP();
}
