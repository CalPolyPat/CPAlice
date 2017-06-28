for f in ./plotsKlayWeakNoSSNoSig/*; do
	if [ -f "$f" ]; then
		mv "$f" "${f/>/-}"
	fi
done

for f in ./plotsKlayWeakNoSSSig/*; do
	if [ -f "$f" ]; then
		mv "$f" "${f/>/-}"
	fi
done
