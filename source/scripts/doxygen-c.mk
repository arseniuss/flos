
PROJECT_NAME?=Unnamed project



generate-docs:
	docygen <<< EOF
	
		DOXYFILE_ENCODING      = UTF-8
		PROJECT_NAME           = "$(PROJECT_NAME)"
	
	EOF
