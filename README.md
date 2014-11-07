# Drush Drupal Status (drush_drupal_status)

## Introduction

Prints the Drupal status report table (Admin > Reports > Status) on the command line.
In other words, it prints out every module that implements `hook_requirements()`... 

## Commands

drupal-status

## Requirements

Since this is a Drush extension, you will need Drush >=v.5.

## Installation

### Manual method

Download from project page and extract this extension to a number of places:

- In a .drush folder in your HOME folder.
- Along with one of your existing modules. If your command is related to an existing module, this is the preferred option.
- In a folder specified with the include option.
- In /path/to/drush/commands (not a "Smart Thing to Do", but it would work).

### Drush method 

Since this is as drupal.org project, you might install it via drush, just type:
	
    drush dl drush_drupal_status

