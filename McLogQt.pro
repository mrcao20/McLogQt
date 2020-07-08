TEMPLATE = subdirs

SUBDIRS += McLogQt

SUBDIRS += Test
Test.depends += McLogQt
