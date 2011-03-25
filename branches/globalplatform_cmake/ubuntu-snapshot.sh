#!/bin/bash

UBUNTU_DISTS="dapper hardy jaunty karmic lucid maverick natty"

PACKAGE=`sed -n -e 's/PROJECT(\(.*\) .*)/\1/p' CMakeLists.txt`
VERSION=`sed -n -e 's/SET(VERSION "\(.*\)")/\1/p' CMakeLists.txt`

echo "Using package name : ${PACKAGE}"
echo "Using version      : ${VERSION}"

RELEASE_VERSION=`cat ubuntu.version`

SNAPSHOT_VERSION=$((${RELEASE_VERSION}-1))+${RELEASE_VERSION}-SNAPSHOT-`date +%F-%0k-%0M-%0S%z`

echo "Using Ubuntu snapshot version ${SNAPSHOT_VERSION}"

	rm -rf ${PACKAGE}-${VERSION}
	tar xzf ${PACKAGE}-${VERSION}.tar.gz
	rm -f ${PACKAGE}_${VERSION}.orig.tar.gz
	cd ${PACKAGE}-${VERSION} && dh_make -l -c lgpl -e "k_o_@users.sourceforge.net" -f ../${PACKAGE}-${VERSION}.tar.gz
	cp ${PACKAGE}_${VERSION}.orig.tar.gz lib${PACKAGE}6_${VERSION}.orig.tar.gz
	cd ${PACKAGE}-${VERSION} && rm -rf debian
	cd ${PACKAGE}-${VERSION} && mkdir debian
	cd ${PACKAGE}-${VERSION} && cp ../debian/* debian/
	cd ${PACKAGE}-${VERSION} && chmod 755 debian/rules
	for d in $(UBUNTU_DISTS); \
	do \
		cd ${PACKAGE}-${VERSION}; \
		cp ../debian/changelog debian/; \
		sed -e "s/DISTRO/$$d/g" debian/changelog > debian/changelog.tmp; \
		mv debian/changelog.tmp debian/changelog; \
		sed -e "s/VERSION/$(SNAPSHOT_VERSION)/g" debian/changelog > debian/changelog.tmp; \
		mv debian/changelog.tmp debian/changelog; \
		# change binary:Version with Source-Version for dapper \
		if [ $$d == 'dapper' ] ; then \
			sed -e "s/binary:Version/Source-Version/g" debian/control > debian/control.tmp; \
			mv debian/control.tmp debian/control; \
		else \
			cp ../debian/control debian/ ; \
		fi; \
		debuild --no-tgz-check -S; \
	done

