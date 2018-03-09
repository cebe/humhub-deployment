

CREATEMODULES=$(patsubst modules/%,humhub/protected/modules/%,$(wildcard modules/*))
CREATETHEMES=$(patsubst themes/%,humhub/themes/%,$(wildcard themes/*))

COMPOSER_FLAGS=
ENV=dev
PORT=8080

ifeq '$(ENV)' 'prod'
COMPOSER_FLAGS="$(COMPOSER_FLAGS) --no-dev"
endif

all:
	@echo "Run  make deploy  for deployment."
	@echo "     make start   to start PHP built-in webserver"
	@echo "     make stop    to stop PHP built-in webserver"

deploy: git-submodules refresh-modules $(CREATEMODULES) refresh-themes $(CREATETHEMES) composer

git-submodules:
	git submodule update --init

composer.json: tools/composer.json.dist
	cp $< $@

composer-update: composer.json
	composer update $(COMPOSER_FLAGS)

composer: composer.json
	composer install --no-suggest -o $(COMPOSER_FLAGS)

# TODO figure out how to add a module without touching other dependencies

refresh-modules:
	find humhub/protected/modules -type l -exec rm {} +

humhub/protected/modules/%: modules/%
	ln -sf ../../../$< $@

refresh-themes:
	find humhub/themes -type l -exec rm {} +

humhub/themes/%: themes/%
	ln -sf ../../$< $@


#
## Webserver
#

# start PHP built-in webserver

start: stop
	@echo "Running builtin PHP webserver at http://localhost:$(PORT)"
	@YII_ENV=dev php -S localhost:$(PORT) -t humhub >> php.log & echo "$$!" > php.pid

stop:
	-if [ -f php.pid ] ; then kill $$(cat php.pid); fi
	rm -f php.pid
	# remove PHP sessions
	rm -f session_mm_*.sem

clean: stop
	-rm -f php.log

.PHONY: all deploy refresh-modules refresh-themes composer git-submodules start stop clean

# vim: set syntax=make :
