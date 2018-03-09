Humhub Deployment
=================

Tools for deploying a Humhub installation together with modules.

Starting a new project
----------------------

```
# create empty git repo in current folder
git init .

# add humhub and check out a stable version
git submodule add https://github.com/humhub/humhub humhub
git -C ./humhub checkout v1.2.4
git add humhub

# add this repo
git submodule add https://gitlab.cebe.cc/humhub-dev/humhub-deployment tools
echo "include tools/Makefile.inc" > Makefile
git add Makefile
```

commit your changes and you are ready to go.

Adding Modules
--------------

TBD

Adding Themes
-------------

TBD

Changing Humhub Config
----------------------

TBD

