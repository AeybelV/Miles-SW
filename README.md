# Miles Hexapod Robot - Software

This submodule contains the software the Miles Hexapod Robot.

## Dependencies

- git
- docker
- make

## Compiling

Docker is utilized to handle package management and building
both the OS and robot software.

To build everything, just run

```sh
make # Builds everything
```

OS images and software can be built seperately.

```sh
make software # Builds software
make os # Builds OS Images
```

The results can be found in the output folder.

You can flash to an SD card with

```sh
sudo dd if=build/os/out/<image name>.img of=/dev/<sd device> bs=4M status=progress
```

## License

This project is licensed under the GNU General Public License v3.0 License.
See the [LICENSE](LICENSE) file for details.
