

#ifndef TINTIN_REPORTER_H
# define TINTIN_REPORTER_H

class TintinReporter
{
	public:
		TintinReporter();
		TintinReporter(TintinReporter &other);
		virtual ~TintinReporter();

		TintinReporter	&operator=(TintinReporter &other);

	private:
}

#endif