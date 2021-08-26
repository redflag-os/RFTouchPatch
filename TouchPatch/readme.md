# Redflag TouchPatch

红旗软件触屏校准软件

- cd SOURCES/TouchPatch

- use qt make bin file

- copy bin file to rpmbuild/BUILD/TouchPatch

- copy run_RFTouchPatch.sh RFTouchPatch.png RFTouchPatch.desktop to rpmbuild/BUILD/TouchPatch

- copy RFTouchPatch.spec to rpmbuild/SPECS

- cd rpmbuild/SPECS

- rpmbuild -ba RFTouchPatch.spec

