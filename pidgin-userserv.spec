%global pidgin_version 2.0.0

Name:		pidgin-userserv
Version:	0.2
Release:	1%{?dist}
Summary:	Send a login to USERSERV

Group:		Applications/Internet
License:	GPLv2
URL:		https://github.com/wolfc/userserv/
Source0:	pidgin-userserv.tar.gz

BuildRequires:	libpurple-devel >= %{pidgin-version}

Requires:	pidgin >= %{pidgin_version}

%description


%prep
%setup -q -n pidgin-userserv


%build
make %{?_smp_mflags}


%install
make install DESTDIR=%{buildroot}


%files
%doc
%{_libdir}/pidgin/userserv.so



%changelog

