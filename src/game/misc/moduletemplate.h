/**
 * File: moduletemplate.h
 *
 * Description: Header file for a module
 */
#ifndef MODULETEMPLATE_H
#define MODULETEMPLATE_H

/// Template for a data system
/// Used to make a standard interface to create instance systems,
/// with some helper functions
class cDataSystem {
    public:
        /// Function to initialize the data system
        virtual void init(void)=0;
        
        /// Function to initialize called for every level change
        virtual void level_init(void)=0;

        /// Function to load all data for a module
        virtual int load(void)=0;
        
        /// Function to process data
        virtual void process(double delta)=0;
        
        /// Function to draw a data instance
        virtual void draw(void)=0;
        
        /// Function to eliminate all data in module
        virtual void clear_data()=0;
};

#endif

