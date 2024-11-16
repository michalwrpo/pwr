# -----------------
# Script getting images from Cat API and jokes from Chuck Norris API and displaying them in terminal
# Michał Waluś 2024
# -----------------

TEXT=$(curl -s https://api.chucknorris.io/jokes/random | jq -r '.value')
IMAGE_URL=$(curl -s https://api.thecatapi.com/v1/images/search | jq -r '.[0].url')

curl -s ${IMAGE_URL} | catimg -

echo $TEXT
