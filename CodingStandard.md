# General #
Indentation size set to 4, all spaces.

Preferably using K&R style ([link](http://en.wikipedia.org/wiki/Indent_style#K.26R_style)) for indentation, but deviations are acceptable.


## Classes ##
Module class declarations are prefixed 'cm', and their singleton definitions [always](are.md) in mGame, prefixed 'm'. Other classes are always prefixed 'c', and struct[ures](ures.md) always 's'.

```
class cmModule {
    public:
        // stuff
};

class cmGame {
    public:
        // Modules
        cmModule *mModule;
};
```

Note also that game.h NEVER includes any files, all module are forward declared.

As hinted above, class declarations are done in the following way:
```
class cClass {
// Indent for each of private/public/etc. after opening brace
    private:
        // Indent for private stuff

    public:
        // Indent for public stuff
};
```

## Functions ##
Both out-of-class and in-class functions should preferably have the form **function\_name()**, all lowercase and each word separated by an underscore.

## Variables ##
Class variables should have the form **variableName**, first word lowercase (though this is open for discussion), then an uppercase letter separating each successive word. This should distinguish variable names enough from function names.

# Commenting style #
Everything **MUST** be commented in full and proper! And if you've got nothing to work on currently for the project, just find some badly commented code and fix it up.

## Functions ##
A function should preferably be separated into easily visible distinct sections of code, each prefaced with a comment describing the section. The comment before each function is for doxygen to handle, so if you feel the need for additional tags, consult the doxygen documentation.
```
/**
 * Description of the function here.
 * Notice the style of the comment
 * @param Parameter Description of parameter
 * @param Par2 Desc. of par 2
 */
void function_name(int Parameter, int Par2)
{
    // Description of first section of code
    [stuff]

    // Description of second section
    [moar stuff]
}
```

## Classes ##
Classes should be divided into sections. Sections starts with function declarations, then variable declarations. This documentation style is primarily for doxygen documentation, but it makes each class much more readable.
```
/**
 * Description of class
 */
class cClass {
    public:
        /// @name Short name for section
        //@{ <-- Opening brace for section, read by doxygen.
            void function1();
            void function2();

            int varName;
        //@}

        /// @name Next section
        //@{
            void function3();
            void different_name();

            int moreStuff;
        //@}
};
```