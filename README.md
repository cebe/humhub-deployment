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

# composer.json is managed by the Makefile, so ignore it in git
echo "/composer.json" > .gitignore
git add .gitignore
```

commit your changes and you are ready to go.

Adding Modules
--------------

Add modules by putting them into the `modules` folder. This will
be synced with humhub on deployment.

You can develop custom modules directly in your repo, or add other modules as
git submodules. For example, adding the custom-pages module:

```
git submodule add https://github.com/humhub/humhub-modules-custom-pages modules/custom_pages
```

and optionally check out a specific version.

Adding Themes
-------------

Add themes by putting them into the `themes` folder. This will
be synced with humhub on deployment.

You can develop custom modules directly in your repo, or add other themes as
git submodules.

Changing Humhub Config
----------------------

TBD


Installing Additional composer packages
---------------------------------------

For allowing to add additional composer packages without touching the original composer.json file
provided by humhub, we use the [wikimedia/composer-merge-plugin](https://github.com/wikimedia/composer-merge-plugin).

You should ignore `composer.json` in `.gitignore` as this file is manged by the `Makefile`.
If you want to add custom packages, create a `composer.local.json` file and specify all
requirements and autoloading definitions there.





