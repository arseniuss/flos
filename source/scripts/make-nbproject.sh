

echo "This script creates NetBeans 8.2 project"
read -p "Enter project name: " PROJECT_NAME

if [ -d nbproject ]; then 
    rm -rf nbproject
fi

mkdir nbproject

cat <<EOF > nbproject/configurations.xml
<?xml version="1.0" encoding="UTF-8"?>
<configurationDescriptor version="100">
  <logicalFolder name="root" displayName="root" projectFiles="true" kind="ROOT">
    <df root="." name="0">
      <df name="csource">
      </df>
    </df>
    <logicalFolder name="ExternalFiles"
                   displayName="Important Files"
                   projectFiles="false"
                   kind="IMPORTANT_FILES_FOLDER">
      <itemPath>build.mk</itemPath>
      <itemPath>config.mk</itemPath>
      <itemPath>makefile</itemPath>
    </logicalFolder>
  </logicalFolder>
  <sourceFolderFilter>^(nbproject)$</sourceFolderFilter>
  <sourceRootList>
    <Elem>.</Elem>
  </sourceRootList>
  <projectmakefile>makefile</projectmakefile>
  <confs>
    <conf name="amd64-flos-linux" type="0">
      <toolsSet>
        <compilerSet>flos-clang|CLang</compilerSet>
        <dependencyChecking>false</dependencyChecking>
        <rebuildPropChanged>false</rebuildPropChanged>
      </toolsSet>
      <flagsDictionary>
        <element flagsID="0" commonFlags="-fPIC"/>
      </flagsDictionary>
      <codeAssistance>
      </codeAssistance>
      <makefileType>
        <makeTool>
          <buildCommandWorkingDir>.</buildCommandWorkingDir>
          <buildCommand>make all ARCH=amd64 OS=flos HOST=linux VERBOSE=1</buildCommand>
          <cleanCommand>make clean ARCH=amd64 OS=flos HOST=linux VERBOSE=1</cleanCommand>
          <executablePath></executablePath>
        </makeTool>
        <preBuild>
          <preBuildCommandWorkingDir>.</preBuildCommandWorkingDir>
          <preBuildCommand></preBuildCommand>
        </preBuild>
      </makefileType>
    </conf>
    <conf name="arm64-flos-linux" type="0">
      <toolsSet>
        <compilerSet>flos-clang|CLang</compilerSet>
        <dependencyChecking>false</dependencyChecking>
        <rebuildPropChanged>false</rebuildPropChanged>
      </toolsSet>
      <flagsDictionary>
        <element flagsID="0" commonFlags="-fPIC"/>
      </flagsDictionary>
      <codeAssistance>
      </codeAssistance>
      <makefileType>
        <makeTool>
          <buildCommandWorkingDir>.</buildCommandWorkingDir>
          <buildCommand>make all ARCH=arm64 OS=flos HOST=linux VERBOSE=1</buildCommand>
          <cleanCommand>make clean ARCH=arm64 OS=flos HOST=linux VERBOSE=1</cleanCommand>
          <executablePath></executablePath>
        </makeTool>
        <preBuild>
          <preBuildCommandWorkingDir>.</preBuildCommandWorkingDir>
          <preBuildCommand></preBuildCommand>
        </preBuild>
      </makefileType>
    </conf>
    <conf name="x86-flos-linux" type="0">
      <toolsSet>
        <compilerSet>flos-clang|CLang</compilerSet>
        <dependencyChecking>false</dependencyChecking>
        <rebuildPropChanged>false</rebuildPropChanged>
      </toolsSet>
      <flagsDictionary>
        <element flagsID="0" commonFlags="-fPIC"/>
      </flagsDictionary>
      <codeAssistance>
      </codeAssistance>
      <makefileType>
        <makeTool>
          <buildCommandWorkingDir>.</buildCommandWorkingDir>
          <buildCommand>make all ARCH=x86 OS=flos HOST=linux VERBOSE=1</buildCommand>
          <cleanCommand>make clean ARCH=x86 OS=flos HOST=linux VERBOSE=1</cleanCommand>
          <executablePath></executablePath>
        </makeTool>
        <preBuild>
          <preBuildCommandWorkingDir>.</preBuildCommandWorkingDir>
          <preBuildCommand></preBuildCommand>
        </preBuild>
      </makefileType>
    </conf>
  </confs>
</configurationDescriptor>

EOF

cat <<EOF > nbproject/project.xml
<?xml version="1.0" encoding="UTF-8"?>
<project xmlns="http://www.netbeans.org/ns/project/1">
    <type>org.netbeans.modules.cnd.makeproject</type>
    <configuration>
        <data xmlns="http://www.netbeans.org/ns/make-project/1">
            <name>${PROJECT_NAME}</name>
            <c-extensions>c</c-extensions>
            <cpp-extensions/>
            <header-extensions>h</header-extensions>
            <sourceEncoding>UTF-8</sourceEncoding>
            <make-dep-projects/>
            <sourceRootList>
                <sourceRootElem>.</sourceRootElem>
            </sourceRootList>
            <confList>
                <confElem>
                    <name>amd64-flos-linux</name>
                    <type>0</type>
                </confElem>
                <confElem>
                    <name>arm64-flos-linux</name>
                    <type>0</type>
                </confElem>
                <confElem>
                    <name>x86-flos-linux</name>
                    <type>0</type>
                </confElem>
            </confList>
            <formatting>
                <project-formatting-style>false</project-formatting-style>
            </formatting>
        </data>
    </configuration>
</project>

EOF
