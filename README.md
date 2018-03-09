Humhub Deployment
=================

This repostiroy provides reliable deployments for Humhub.
It allows you to install Humhub with a defined set of modules, themes and custom configuration.

It is using git submodules to handle dependencies and a `Makefile` to
glue everything together on deployment.

Requirements
------------

- [Composer](https://getcomposer.org/doc/00-intro.md#globally) installed and availble as `composer` command in your PATH.
- [GNU Make](https://www.gnu.org/software/make/)
- HumHub 1.3-dev or higher

Starting a new project
----------------------

```bash
# create empty git repo in current folder
git init .

# add humhub and check out a stable version
git submodule add https://github.com/humhub/humhub humhub
git -C ./humhub checkout v1.3-dev
git add humhub

# add this repo
git submodule add https://github.com/cebe/humhub-deployment tools
echo "include tools/Makefile.inc" > Makefile
git add Makefile

# composer.json is managed by the Makefile, so ignore it in git
echo "/composer.json" > .gitignore
git add .gitignore
```

commit your changes and you are ready to go.

Deployment
----------

Run `make deploy` in dev env or `make deploy ENV=prod` in production.

For development, `make start` and `make stop` provide shortcuts for starting
the PHP builtin webserver. Use `make start PORT=1234` to specify a different port to use.

Customization
-------------

### Adding Modules

Add modules by putting them into the `modules` folder. This will
be synced with humhub on deployment.

You can develop custom modules directly in your repo, or add other modules as
git submodules. For example, adding the custom-pages module:

```bash
git submodule add https://github.com/humhub/humhub-modules-custom-pages modules/custom_pages
```

and optionally check out a specific version.

Module may provide a `composer.json` file to specify additional dependencies to be installed.

### Adding Themes

Add themes by putting them into the `themes` folder. This will
be synced with humhub on deployment.

You can develop custom themes directly in your repo, or add other themes as
git submodules.

### Changing Humhub Config

TBD


### Installing Additional composer packages

For allowing to add additional composer packages without touching the original composer.json file
provided by humhub, we use the [wikimedia/composer-merge-plugin](https://github.com/wikimedia/composer-merge-plugin).

You should ignore `composer.json` in `.gitignore` as this file is manged by the `Makefile`.
If you want to add custom packages, create a `composer.local.json` file and specify all
requirements and autoloading definitions there.
The `composer.lock` file should be committed to the repository as it tracks the exact versions
of installed packages and allows reliable deplyoments.

For updating packages, run `composer update` as you would normally do.



