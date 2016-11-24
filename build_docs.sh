#!/bin/bash
# NOTE: Couscous bin should be in the PATH!!

# Generate couscous docs in .couscous/generated
couscous generate

if [[ $? -ne 0 ]]
then
  echo "Cosucous failed!"
  exit 1
fi

COUSCOUS_GENERATED=".couscous/generated"

# Copy folders into website
cp -r "${COUSCOUS_GENERATED}/css" "${COUSCOUS_GENERATED}/doc" "${COUSCOUS_GENERATED}/fonts" "${COUSCOUS_GENERATED}/img" "${COUSCOUS_GENERATED}/js" "./website"

# Restore
#rm -r ./website
#git checkout -- website/
