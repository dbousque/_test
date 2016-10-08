

#include "IMateriaSource.hpp"
#include "MateriaSource.hpp"
#include "ICharacter.hpp"
#include "Character.hpp"
#include "Ice.hpp"
#include "Cure.hpp"

int main()
{
	IMateriaSource* src = new MateriaSource();
	src->learnMateria(new Ice());
	src->learnMateria(new Cure());

	ICharacter* zaz = new Character("zaz");

	AMateria* tmp;
	tmp = src->createMateria("ice");
	zaz->equip(tmp);
	tmp = src->createMateria("cure");
	zaz->equip(tmp);

	ICharacter* bob = new Character("bob");

	std::cout << "tmp xp beofore materia uses : " << tmp->getXP() << std::endl;
	zaz->use(0, *bob);
	std::cout << "tmp xp after other materia use  : " << tmp->getXP() << std::endl;
	zaz->use(1, *bob);
	std::cout << "tmp xp after own use : " << tmp->getXP() << std::endl;

	std::cout << "Adding three other materias to the materiaSource, should only be able to add the first two of them" << std::endl;
	src->learnMateria(new Ice());
	src->learnMateria(new Cure());
	src->learnMateria(new Ice());

	std::cout << "Equiping zaz until full" << std::endl;
	zaz->equip(src->createMateria("cure"));
	zaz->equip(src->createMateria("cure"));
	zaz->equip(src->createMateria("cure"));

	std::cout << "using new materias" << std::endl;
	zaz->use(2, *bob);
	zaz->use(3, *bob);
	std::cout << "calling zaz->use(4, *bob) should do nothing : " << std::endl;
	zaz->use(4, *bob);

	std::cout << std::endl << "using tmp again, and showing xp : " << std::endl;
	zaz->use(1, *bob);
	std::cout << "tmp xp : " << tmp->getXP() << std::endl;

	delete bob;
	delete zaz;
	delete src;

	return 0;
}