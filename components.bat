pushd .\include\components\
rose.parser -I .\padevents.h .\workspace.h .\path.h -O .\components_ser.h
rose.parser -I .\engine\recording.h -O .\engine\recording.serializer.hpp
popd

pushd .\include\rose\raylibutils
rose.parser -I types.h -O types.serializer.h
popd
