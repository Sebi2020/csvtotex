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
		sh 'gzip -c ./src/csvtotex > csvtotex.zip'
		archiveArtifacts artifacts: '*.zip'
	}
	}
}
}
