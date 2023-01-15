pushd .\include\components\
rose.parser -I .\padevents.h .\workspace.h .\path.h -O .\components_ser.h
rose.parser -I .\events\recordingevents.h -O .\events\recordingevents.serializer.hpp
popd
