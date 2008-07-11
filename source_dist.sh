#!/bin/sh

SCRIPT_PATH=`dirname $0`;

PKGDIR=bncsutil-`cat $SCRIPT_PATH/product_version`
rm -fr $PKGDIR
mkdir $PKGDIR

for b in config configure doc product_version src support tests vb6_example \
	vc7_build vc8_build windows_dist.bat source_dist.sh windows_dist.sh \
	README-Windows.txt
do
	cp -R $SCRIPT_PATH/$b $PKGDIR
done

rm -f $PKGDIR.tar.bz2
rm -f $PKGDIR.tar.gz

tar --exclude=.svn -cjvf $PKGDIR.tar.bz2 $PKGDIR
tar --exclude=.svn -czvf $PKGDIR.tar.gz $PKGDIR

rm -fr $PKGDIR

scp $PKGDIR.tar.bz2 $PKGDIR.tar.gz "ionws.com:/home/ericn/public_html/code/bncsutil/static/releases"
