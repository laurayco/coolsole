#ifndef __coolsole__hpp

#include <iostream>
#include <stack>

#ifdef _WIN32
	#include <windows.h>
#endif

#ifndef nullptr
#define nullptr NULL
#endif

namespace Coolsole
{

	class ColorState;
	class FormattedOutput;

	template<typename>
	class SingletonContainer;

	/*
		Color Codes found here:
			http://en.wikipedia.org/wiki/ANSI_escape_code#Colors
	*/
	enum Color {
			Black = 0,
			Blue = 1,
			Green = 2,
			Aqua = 3,
			Red = 4,
			Purple = 5,
			Yellow = 6,
			White = 7,
			Gray = 8,
			BrightBlue = 9,
			BrightGreen = 10,
			BrightAqua = 11,
			BrightRed = 12,
			BrightPurple = 13,
			BrightYellow = 14,
			BrightWhite = 15
	};


	/*
		This class is entirely not
		necessary. It's just here
		for the sake of inheritance,
		and practical extendability.
	*/
	class ColorState
	{
	protected:
		std::stack<Color> colors;
	public:
		virtual void push_color(Color);
		virtual Color pop_color();
		operator Color () const;
		Color current_color() const;
		ColorState(Color);
	};

	/*
		Again, here simply for the purpose
		of inheritance. Maybe adding an
		HTML-output could be a good idea.
		Could base this on detecting
		CGI, and returnning a HTML-output
		instance in the get_console()
		function or something. That would
		be pretty cool, jyah?
	*/
	class FormattedOutput
	{
	public:
		Color foreground() const;
		Color background() const;
		void foreground(Color);
		void background(Color);
		void previous_foreground();
		void previous_background();
	protected:
		ColorState _foreground, _background;
		FormattedOutput();
		virtual void set_state(Color,Color)=0;
	};

	template<typename Type>
	class SingletonContainer
	{
		protected:
			Type* instance;
			virtual Type* make_instance() = 0;
		public:
		SingletonContainer(Type* ptr = nullptr):
			instance(ptr)
		{
		}

		Type& get_instance()
		{
			if(instance!=nullptr)
			{
				return *instance;
			}
			instance = make_instance();
			return *instance;
		}

		~SingletonContainer()
		{
			if(instance!=nullptr)
			{
				delete instance;
			}
		}
	};

	/*
		Because only std::out will support
		any kind of text formatting,
		we will make this a singleton type
		object. Notice however, that this
		singleton instance does inherit
		from the potentially non-singleton
		FormattedOutput class.
	*/
	class ConsoleOutput: public FormattedOutput
	{
	public:
		class ConsoleSingleton: public SingletonContainer<ConsoleOutput>
		{
			protected:
				virtual ConsoleOutput* make_instance()
				{
					#ifdef _WIN32
						return new ConsoleOutput(GetStdHandle( STD_OUTPUT_HANDLE ));
					#else
						return new ConsoleOutput();
					#endif
				}
		};
		virtual void set_state(Color,Color);
		#ifdef _WIN32
			ConsoleOutput(HANDLE);
		#else
			ConsoleOutput();
		#endif
		virtual ~ConsoleOutput();
		#ifdef _WIN32
		    HANDLE console_handle;
			CONSOLE_SCREEN_BUFFER_INFO original_csbi;
		#endif
		static ConsoleSingleton Singleton;
	};

}

#endif
