pipeline {
agent any
stages {
	stage('Configure') {
	steps {
		sh 'cmake "CMakeLists.txt"'
	}
	}
	stage('Build') {
	steps {
		sh 'make'
	}
	}
	stage('Package') {
	steps {
		sh 'gzip -c csvtotex > csvtotex.zip'
		archiveArtifacts artifact: '*.zip'
	}
	}
}
}
