Draggable References
====================

This is an attempt at a 'Configurable Feature' for Drupal. It consists of a
default panel, view and variable override to setup a nice UI for adding and
ordering a child content type which has a nodereference to a parent content
type. It attempts to make the content types themselves ambiguous by giving you
a setting page to control which is the parent, which is the child.

Dependencies
------------

@see dragref.info

Instructions
------------

* Download and install this module and it's dependencies.
* Enable this module which will enable it's dependencies.
* Create a 'Parent' content type. Page is used by default.
* Create a 'Child' content type. Story is used by default.
* On your 'Child' content type, create a new 'Node Reference' field with the 
  'Reference from URL' widget provided by the nodereference_url module which
  references your 'Parent' content type.
* Go to /admin/settings/dragref and tell it which node type is your 'Parent'
  and which node type is your 'Child'.

Known bugs
----------
* There is currently a bug with altering the default view provided.
* We should check to make sure that the child noderef point to the parent.