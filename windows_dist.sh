#!/bin/sh

SCRIPT_PATH=`dirname $0`;
PKGDIR=bncsutil-`cat $SCRIPT_PATH/product_version`
FILES=""

for config in Release Debug
do
	vcbuild /u /r /nologo /htmllog:./$config/BuildLog.html $SCRIPT_PATH/vc8_build/BNCSutil.vcproj $config
	rm -f $PKGDIR-$config.zip
	mkdir $PKGDIR
	
	for f in BNCSutil.dll BNCSutil.lib BNCSutil.pdb BuildLog.html
	do
		cp $SCRIPT_PATH/vc8_build/$config/$f $PKGDIR/$f
	done
	
	mkdir $PKGDIR/bncsutil
	for f in $SCRIPT_PATH/src/bncsutil/*.h
	do
		cp $f $PKGDIR/bncsutil/`basename $f`
	done
	
	cp vb6_example/BNCSutil.bas $PKGDIR
	cp vb6_example/NLS.cls $PKGDIR
	
	zip -9q -r $PKGDIR-$config.zip $PKGDIR
	rm -fr $PKGDIR
	
	FILES="$FILES $PKGDIR-$config.zip"
done

zip -9q -r ${PKGDIR}_vb_example.zip vb6_example
FILES="$FILES ${PKGDIR}_vb_example.zip"

pscp $FILES "ericn@ionws.com:/home/ericn/public_html/code/bncsutil/static/releases"