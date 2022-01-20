set(DOCFILES
  Diagrams.mdj
)

source_group("Diagrams" FILES ${DOCFILES})

add_custom_target(docs
  ${DOCFILES}
)
