pipeline {
agents { docker { image: 'library/gcc' }}
stages {
	stage('Build') {
		sh 'cmake "CMakeLists.txt"'		
	}
	stage('Package') {
		sh 'gzip -c csvtotex > csvtotex.zip'
		archiveArtifacts artifact: '*.zip'
	}
}
}
