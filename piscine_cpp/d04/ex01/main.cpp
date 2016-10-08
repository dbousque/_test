

#include "PlasmaRifle.hpp"
#include "PowerFist.hpp"
#include "SuperMutant.hpp"
#include "RadScorpion.hpp"
#include "Character.hpp"
#include "Enemy.hpp"
#include "AWeapon.hpp"

void		testWeaponsEnemies(void)
{
	PlasmaRifle plasma;
	PowerFist	power;
	SuperMutant	mutant;
	RadScorpion	scorpion;

	plasma.attack();
	power.attack();
	mutant.takeDamage(50);
	mutant.takeDamage(200);
}

int main()
{
	Character* zaz = new Character("zaz");

	std::cout << *zaz;

	Enemy* b = new RadScorpion();

	AWeapon* pr = new PlasmaRifle();
	AWeapon* pf = new PowerFist();

	zaz->equip(pr);
	std::cout << *zaz;
	zaz->equip(pf);

	zaz->attack(b);
	std::cout << *zaz;
	zaz->equip(pr);
	std::cout << *zaz;
	zaz->attack(b);
	std::cout << *zaz;
	zaz->attack(b);
	std::cout << *zaz;

	std::cout << std::endl << "Testing some other weapons and ennemies : " << std::endl;
	testWeaponsEnemies();
	std::cout << "Calling recoverAP() 3 times on Character zaz : " << std::endl;
	std::cout <<* zaz;
	zaz->recoverAP();
	std::cout << *zaz;
	zaz->recoverAP();
	std::cout << *zaz;
	zaz->recoverAP();
	std::cout << *zaz;
	return 0;
}