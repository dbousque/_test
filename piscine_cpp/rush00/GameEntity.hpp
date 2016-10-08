

#ifndef GAMEENTITY_H
# define GAMEENTITY_H

class GameEntity
{
	public:
		GameEntity(int start_x, int start_y, std::string *representation, int repr_height);
		GameEntity(GameEntity &other)
		~GameEntity();

		GameEntity	&operator(GameEntity &other);
		int			getX() const;
		int			getY() const;
		void		move(int dx, int dy);
		bool		touches(GameEntity &other) const;
		std::string	*getRepresentation() const;
		int			getReprLen() const;
		int			getReprHeight() const;
		int			getReprLenAtScale() const;
		int			getReprHeightAtScale() const;
		void		display() const;

	protected:
		std::string	*_repr;
		int			_repr_height;
		int			_repr_height_at_scale;
		int			x;
		int			y;

	private:
		GameEntity();
};

#endif