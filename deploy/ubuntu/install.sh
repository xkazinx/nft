#!/usr/bin/env bash
# Installs nft on the Ubuntu box from an uploaded folder (deploy_ubuntu.ps1 sends it
# to /tmp/nft-upload): the web build under /opt/nft/web, Caddy's snippet in
# /etc/caddy/sites/kazin.dev.d/ (Caddy restarted only when the snippet changed: its
# admin API is off). No service: the page is static.
#   sudo bash install.sh [<upload folder>]
set -euo pipefail
SRC="${1:-/tmp/nft-upload}"
SNIPPET=/etc/caddy/sites/kazin.dev.d/nft.caddy

install -d -m 755 /opt/nft

# The web build swapped whole (a visitor never gets half of two builds)
rm -rf /opt/nft/web.new
cp -r "$SRC/web" /opt/nft/web.new
chmod -R a+rX /opt/nft/web.new
rm -rf /opt/nft/web.old
[ -d /opt/nft/web ] && mv /opt/nft/web /opt/nft/web.old
mv /opt/nft/web.new /opt/nft/web
rm -rf /opt/nft/web.old

if ! cmp -s "$SRC/nft.caddy" "$SNIPPET"; then
	[ -f "$SNIPPET" ] && cp "$SNIPPET" "$SNIPPET.bak"
	install -m 644 "$SRC/nft.caddy" "$SNIPPET"
	if ! caddy validate --config /etc/caddy/Caddyfile --adapter caddyfile >/tmp/nft-caddy.log 2>&1; then
		echo "(!) Caddy refused the snippet:"; tail -5 /tmp/nft-caddy.log
		if [ -f "$SNIPPET.bak" ]; then mv -f "$SNIPPET.bak" "$SNIPPET"; else rm -f "$SNIPPET"; fi
		exit 1
	fi
	rm -f "$SNIPPET.bak"
	systemctl restart caddy
	echo "Caddy: snippet installed, restarted"
fi

ls -la /opt/nft/web
