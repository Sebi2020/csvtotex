pipeline {
agent any
stages {
	stage('Configure') {
		sh 'cmake "CMakeLists.txt"'		
	}
	stage('Build') {
		sh 'make'
	}
	stage('Package') {
		sh 'gzip -c csvtotex > csvtotex.zip'
		archiveArtifacts artifact: '*.zip'
	}
}
}
