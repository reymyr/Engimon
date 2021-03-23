#include "Player.hpp"
#include <iostream>
#include "../Engimon/Engimon.h"
#include "../Engimon/EngimonFactory.h"
#include "../Skill/skill.hpp"
#include "../Skill/skillitem.hpp"
#include "Inventory.hpp"
using namespace std;

Player::Player() : MaxCapacity(20) {
}

Player::Player(std::string starter_name, int species) : MaxCapacity(20) {
  Engimon starterEngimon = EngimonFactory::createEngimon(starter_name, species);  // <- ini engimon starter, bisa dipilih atau engga(?)
  this->activeEngimon = starterEngimon;
}

// getter
Inventory<Engimon> Player::getInventoryEngimon() const {
  return this->inventoryEngimon;
}

Inventory<SkillItem> Player::getInventorySkill() const {
  return this->inventorySkill;
}

Engimon Player::getActiveEngimon() const {
  return this->activeEngimon;
}

int Player::getMaxCapacity() const{
  return this->MaxCapacity;
}

// set activeEngimon -> asumsi parameter valid
void Player::setActiveEngimon(Engimon _engimon) {
  this->activeEngimon = _engimon;
}

bool Player::isInventoryFull() {  // true kalo boleh ditambahin -> otomatis
                                  // maksimum MaxCapacity - 1
  int count = 0;
  count += inventoryEngimon.countItemInInventory();

  typename std::vector<SkillItem>::iterator it = inventorySkill.getContainer().begin();

  int i = 0;
  while (it != inventorySkill.getContainer().end()) {
    count += inventorySkill[i].getItemAmount();
    i++;
    it++;
  }

  if (count < MaxCapacity) {
    return true;
  } else {
    return false;
  }
}

void Player::addToInvEngimon(Engimon engi) {
  if (!isInventoryFull()) {
    this->inventoryEngimon.addToInventory(engi);
  } else {
    std::cout << "Inventory Full!" << std::endl;
  }
}

void Player::addToInvSkill(string _skill) {
  if (!isInventoryFull()) {  // jika tidak full
    typename std::vector<SkillItem>::iterator it = inventorySkill.getContainer().begin();
    int i = 0;
    bool found = false;

    while (!found && it != inventorySkill.getContainer().end()) {
      if (_skill == inventorySkill[i].getSkill().getName()) {
        found = true;
      }

      else {
        it++;
        i++;
      }
    }

    if (found) {  // jika ketemu amount item ditambah
      inventorySkill[i].incrementItemAmount();
    } else {  // lainnya
      SkillItem temp_skillitem(
          1, _skill);  // nanti di SkillItem buat constructor user define
      inventorySkill.addToInventory(temp_skillitem);
    }
  }
}

// Eror
// void Player::removeFromInvSkill() { //menghapus jika amount dari skillitem dalam inventory habis
//   if (this->getMaxCapacity() > 0) {
//     for (auto it = inventorySkill.getContainer().begin(); it != inventorySkill.getContainer().end(); ++it) {
//       if (inventorySkill[it].getItemAmount() == 0) {
//         inventorySkill.erase(it);
//         i--;
//       }
//     }
//   }
// }

Player& Player::operator=(const Player& p) {
  inventoryEngimon = p.inventoryEngimon;
  inventorySkill = p.inventorySkill;
  activeEngimon = p.activeEngimon;

  return *this;
}