

class water =
object
    inherit Molecule.molecule "water" [new Oxygen.oxygen ; new Hydrogen.hydrogen ;
    new Hydrogen.hydrogen]
end
