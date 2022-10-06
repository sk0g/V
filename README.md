# V
UE5 action/roguelike game

# Structure
All custom assets go in [the _ folder](Content/_), while marketplace and sample content go in `Content`. This allows easy in-place updates, as well as a central location for all custom content.

C++ source is in `Source/V`, with headers under the [Public](Source/V/Public) folder, and C++ files under the [Private](Source/V/Private) folder. The C++ code uses `clang-format` for auto formatting, with an (IMO) nice configuration defined in `/.clang-format`. 

Clang-format config takes into account the 'main header', as well as the `*.generated.h` that UHT uses, and automatically sorts them at the end of the import blocks.

## Note
This project uses git-LFS to store binary assets in a secured Azure DevOps repository, along with some hacky LFS config to allow me to host the code on GitHub. As such, cloning this won't grant you access to the binary assets needed to build this project; I don't have the rights to share the assets I am working with, anyway.

If you're trying to clone this, you will need to flip a git flag to skip the LFS checkout. For bash, this could be done in one step: `GIT_LFS_SKIP_SMUDGE=1 git clone ...`

TODO:
- [ ] Screenhots
- [ ] Gameplay description
