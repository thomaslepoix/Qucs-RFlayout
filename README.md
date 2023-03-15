[![Package Debian](https://img.shields.io/github/actions/workflow/status/thomaslepoix/Qucs-RFlayout/release-debian.yml?label=package&logo=debian)](https://software.opensuse.org/download.html?project=home:thomaslepoix:open-rflab&package=qucsrflayout)

# Qucs-RFlayout

## Debian packaging

Here are the instructions to build and install a debian package from upstream sources :

```sh
sudo apt install dpkg-dev

git clone https://github.com/thomaslepoix/Qucs-RFlayout
git clone https://github.com/thomaslepoix/Qucs-RFlayout -b debian debian --depth 1
cd Qucs-RFlayout

git archive \
	--format=tar.gz \
	-o ../qucsrflayout_$(git describe --tags).orig.tar.gz \
	--prefix=qucsrflayout-$(git describe --tags)/ \
	HEAD

mv ../debian/debian .
[ $(git describe --tags) != $(git describe --tags --abbrev=0) ] \
&& sed -i debian/changelog -e "1i \
qucsrflayout ($(git describe --tags)-1) unstable; urgency=medium\n\n\
  * Package from upstream sources\n\n\
 -- Thomas Lepoix <thomas.lepoix@protonmail.ch>  $(date -R)\n\
"

dpkg-buildpackage -b -us -uc

sudo apt install ../qucsrflayout_*.deb
```
