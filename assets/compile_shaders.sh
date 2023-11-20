ARGS=()

while [[ $# -gt 0 ]]; do
	case $1 in
		-D)
			BASE="$2"
			shift
			shift
			;;
		-O)
			TARGET="$2"
			shift
			shift
			;;
		*)
			ARGS+=("$1")
			shift
			;;
	esac
done

for item in "${ARGS[@]}"
do
	DIR=$(dirname $TARGET/$item)
	mkdir -p $DIR
	m4 $BASE/base.m4 $BASE/$item > $TARGET/$item
done