

#ifndef FIELD_H
# define FIELD_H

class Field
{
	public:

		static const char MODULE_TITLE = 1;
		static const char INTEGER = 2;
		static const char INTEGER_PERCENT = 3;
		static const char STRING = 4;
		static const char GRAPH_INT = 5;
		static const char FLOATING = 6;

		Field(void *data, char type);
		Field(Field const &other);
		virtual ~Field();

		Field	&operator=(Field &other);
		void	setId(int id);
		void	*getData() const;
		char	getType() const;
		int		getId() const;

	private:
		Field();

		void	*_data;
		char	_type;
		int		_id;
};

#endif