

CREATEMODULES=$(patsubst modules/%,humhub/protected/modules/%,$(wildcard modules/*))
CREATETHEMES=$(patsubst themes/%,humhub/themes/%,$(wildcard themes/*))

ENV=dev

all:
	@echo "Run  make deploy  for deployment."

deploy: refresh-modules $(CREATEMODULES) refresh-themes $(CREATETHEMES) composer
	git submodule update --init

composer.json: tools/composer.json
	cp $< $@

composer: composer.json
	composer install --no-suggest -o

refresh-modules:
	find humhub/protected/modules -type l -exec rm {} +

humhub/protected/modules/%: modules/%
	ln -sf ../../../$< $@

refresh-themes:
	find humhub/themes -type l -exec rm {} +

humhub/themes/%: themes/%
	ln -sf ../../$< $@

.PHONY: all deploy refresh-modules refresh-themes composer

# vim: set syntax=make :
