#
# RFTouchPatch.spec: spec file
# Copyright (C) 2021, Red Flag Software Co., Ltd
#
Name:	 RFTouchPatch	
Version:1.3
Release:	23
Summary: touch screen Calibration	

Group:	Applications/System	
License: GPLv3+	
URL:	http://www.redflag-os.com	


%description
touch screen Calibration	


%prep


%build


%install
mkdir -p %{buildroot}%{_bindir}
install -m755 ../BUILD/TouchPatch-1.1-1.axs7.aarch64/RFTouchPatch-1.3-8.axs7.aarch64 %{buildroot}%{_bindir}/RFTouchPatch
install -m755 ../BUILD/TouchPatch-1.1-1.axs7.aarch64/run_RFTouchPatch.sh %{buildroot}%{_bindir}/run_RFTouchPatch.sh
install -m755 ../BUILD/TouchPatch-1.1-1.axs7.aarch64/RFTouchPatch.png %{buildroot}%{_bindir}/RFTouchPatch.png
mkdir -p %{buildroot}%{_prefix}/share/applications
install -m755 ../BUILD/TouchPatch-1.1-1.axs7.aarch64/RFTouchPatch.desktop %{buildroot}%{_prefix}/share/applications/RFTouchPatch.desktop

chmod +x %{buildroot}%{_bindir}/run_RFTouchPatch.sh
chmod +x %{buildroot}%{_bindir}/RFTouchPatch
chmod +x %{buildroot}%{_prefix}/share/applications/RFTouchPatch.desktop

%pre
touch /etc/xdg/autostart/jiaozhun.desktop
chmod 777 /etc/xdg/autostart/jiaozhun.desktop
touch /etc/xdg/autostart/jiaozhun.sh
chmod 777 /etc/xdg/autostart/jiaozhun.sh


%files
%{_bindir}/RFTouchPatch
%{_bindir}/run_RFTouchPatch.sh
%{_bindir}/RFTouchPatch.png
%{_prefix}/share/applications/RFTouchPatch.desktop

%changelog
* Thu Aug 26 2021 JackCui <cuilichen@redflag-os.com> - 1.1-1
- Update to 1.1-1
- Upload to git
