for f in ./plotsKlayWeak/*; do
	if [ -f "$f" ]; then
		mv "$f" "${f/>/-}"
	fi
done

for f in ./plotsKlayStrong/*; do
	if [ -f "$f" ]; then
		mv "$f" "${f/>/-}"
	fi
done
