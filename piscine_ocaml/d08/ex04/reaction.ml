

class virtual reaction mols1 =
object
	val _mols_in:Molecule.molecule list = mols1
	val _mols_out:Molecule.molecule list = []

    method virtual get_start: (Molecule.molecule * int) list
    method virtual get_result: (Molecule.molecule * int) list
    method virtual balance: reaction
    method virtual is_balanced: bool
end
