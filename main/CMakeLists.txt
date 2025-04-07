file(GLOB_RECURSE SRCS "main.c" "*.c"
                    "ui/*.c"
                    "ui/custom/*.c" 
                    "ui/generated/*.c" 
                    "ui/generated/guider_customer_fonts/*.c" 
                    "ui/generated/guider_fonts/*.c" 
                    "ui/generated/images/*.c"
                    )

set(include_dirs 
    "." 
    "ui"
    "ui/custom" 
    "ui/generated" 
    "ui/generated/guider_customer_fonts" 
    "ui/generated/guider_fonts" 
    "ui/generated/images" 
    )

idf_component_register(SRCS ${SRCS}
                       INCLUDE_DIRS ${include_dirs}
                       )
