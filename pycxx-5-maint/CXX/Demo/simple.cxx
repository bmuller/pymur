//
//  Copyright (c) 2008 Barry A. Scott
//
//
//  simple_module.cxx
//
//  This module defines a single function.
//
#ifdef _MSC_VER
// disable warning C4786: symbol greater than 255 character,
// nessesary to ignore as <map> causes lots of warning
#pragma warning(disable: 4786)
#endif

#include "CXX/Objects.hxx"
#include "CXX/Extensions.hxx"

#include <assert.h>

class cls: public Py::PythonExtension< cls >
{
public:
    cls()
    {
    }

    virtual ~cls()
    {
    }

    static void init_type(void)
    {
        behaviors().name( "cls" );
        behaviors().doc( "documentation for cls class" );
        behaviors().supportGetattr();

        add_varargs_method( "cls_func", &cls::cls_func );
    }

    // override functions from PythonExtension
    virtual Py::Object getattr( const char *name )
    {
        return getattr_methods( name );
    }

    Py::Object cls_func( const Py::Tuple &args )
    {
        std::cout << "Called with " << args.length() << " normal arguments." << std::endl;
        return Py::None();
    }
};

class simple_module : public Py::ExtensionModule<simple_module>
{
public:
    simple_module()
    : Py::ExtensionModule<simple_module>( "simple" ) // this must be name of the file on disk e.g. simple.so or simple.pyd
    {
        cls::init_type();

        add_varargs_method("cls", &simple_module::factory_cls, "documentation for cls()");
        add_keyword_method("func", &simple_module::func, "documentation for func()");

        // after initialize the moduleDictionary with exist
        initialize( "documentation for the simple module" );

        Py::Dict d( moduleDictionary() );
        d["var"] = Py::String( "var value" );
    }

    virtual ~simple_module()
    {}

private:
    Py::Object func( const Py::Tuple &args, const Py::Dict &kws )
    {
        std::cout << "Called with " << args.length() << " normal arguments." << std::endl;
        Py::List names( kws.keys() );
        std::cout << "and with " << names.length() << " keyword arguments:" << std::endl;
        for( Py::List::size_type i=0; i< names.length(); i++ )
        {
            Py::String name( names[i] );
            std::cout << "    " << name << std::endl;
        }

        return Py::None();
    }

    Py::Object factory_cls( const Py::Tuple &rargs )
    {
        return Py::asObject( new cls );
    }
};

extern "C" void initsimple()
{
#if defined(PY_WIN32_DELAYLOAD_PYTHON_DLL)
    Py::InitialisePythonIndirectPy::Interface();
#endif

    static simple_module* simple = new simple_module;
}

// symbol required for the debug version
extern "C" void initsimple_d()
{ 
    initsimple();
}
