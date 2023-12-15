build:
	arduino-cli compile --fqbn "arduboy-homemade:avr:arduboy" --optimize-for-debug  --output-dir .

release:
	arduino-cli compile --fqbn "arduboy-homemade:avr:arduboy" --build-properties build.project_name=AllYourArdu.hex --output-dir .

gen:
	./image_gen.sh