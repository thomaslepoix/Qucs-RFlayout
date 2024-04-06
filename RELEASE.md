# Release process

- Update `CHANGELOG` and version number in `CMakeLists.txt` and `default.nix`.
- Publish a Github release (RPM package and Windows executable will be automatically produced and uploaded on the release page).
- On `debian` branch, update `debian/changelog`.
- Manually trigger the `Release Debian` Github workflow (deb packages will be produced on OBS).
