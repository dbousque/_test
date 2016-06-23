

class virtual reaction =
object
    method virtual get_start: (molecule * int) list
    method virtual get_result: (molecule * int) list
    method virtual balance: reaction
    method virtual is_balanced: bool
end
