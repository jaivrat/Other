https://www.youtube.com/watch?v=XuSQU5Grv1g

kubectl version

kubectl --help

controlplane ~ ➜  kubectl get nodes
NAME           STATUS   ROLES                  AGE   VERSION
controlplane   Ready    control-plane,master   10m   v1.29.0+k3s1


controlplane ~ ➜  kubectl get nodes -o wide
NAME           STATUS   ROLES                  AGE   VERSION        INTERNAL-IP    EXTERNAL-IP   OS-IMAGE             KERNEL-VERSION   CONTAINER-RUNTIME
controlplane   Ready    control-plane,master   12m   v1.29.0+k3s1   192.14.212.9   <none>        Alpine Linux v3.16   5.4.0-1106-gcp   containerd://1.7.11-k3s2


ontrolplane ~ ➜  kubectl run nginx
error: required flag(s) "image" not set


controlplane ~ kubectl run nginx --image=nginx
pod/nginx created

controlplane ~ ➜  kubectl get pods
NAME    READY   STATUS    RESTARTS   AGE
nginx   1/1     Running   0          27s


pod-definition.yml
==================
apiVersion:
kind:
metadata:
spec:


pod-definition.yml
===================
apiVersion: v1
kind: Pod
metadata: 
  name: myapp-pod
  labels:
    app: myapp
spec:
  containers:
    - name: nginx-container
      image: nginx
	
controlplane ~ ➜  kubectl create -f pod-definition.yml 
pod/myapp-pod created


controlplane ~ ➜   kubectl get pods
NAME        READY   STATUS    RESTARTS   AGE
nginx       1/1     Running   0          8m58s
myapp-pod   1/1     Running   0          35s


#Detailed--
controlplane ~ ➜  kubectl describe pod myapp-pod 
Name:             myapp-pod
Namespace:        default
Priority:         0



Another example: pod.yml
===================
apiVersion: v1
kind: Pod
metadata: 
  name: myapp-pod
  labels:
    app: myapp
	tier: frontend
spec:
  containers:
    - name: nginx-container
      image: nginx
    - name: busybox-container
      image: busybox  
	  
kubectl create -f pod-definition.yml 
or
kubectl apply -f pod-definition.yml 



controlplane ~ ➜  kubectl run nginx --image=nginx
pod/nginx created

controlplane ~ ➜  kubectl get pods
NAME            READY   STATUS    RESTARTS   AGE
nginx           1/1     Running   0          3m57s
newpods-mx2d5   1/1     Running   0          12s
newpods-kh226   1/1     Running   0          12s
newpods-txxfm   1/1     Running   0          12s

controlplane ~ ➜  kubectl describe pod newpods-mx2d5


controlplane ~ ➜  kubectl delete pod webapp
pod "webapp" deleted

 kubectl run redis --image=redis123
 

controlplane ~ ➜  cat pod-definition.yml 
apiVersion: v1
kind: Pod
metadata: 
  name: myapp-pod
  labels:
    app: myapp
spec:
  containers:
    - name: redis
      image: redis123
	  
	  
controlplane ~ ➜  kubectl create -f pod-definition.yml 
pod/myapp-pod created




-----------------------------------------------------
-------------REPLICASETS-----------------------------
-----------------------------------------------------

replicaset-definition.yml
-------------------------
controlplane ~ ➜  cat replicaset-definition.yml 
apiVersion: apps/v1
kind: ReplicaSet
metadata: 
  name: myapp-replicaset
  labels:
    app: myapp
    type: front-end
spec:
  template:
    # This is copy of one of the pods we created above
    # from metadata
    metadata: 
      name: myapp-pod
      labels:
        app: myapp
        type: front-end
    spec:
      containers:
      - name: nginx-container
        image: nginx
  
  replicas: 3 # NUmber of replicas we need
  selector:
     matchLabels:
       type: front-end
  

controlplane ~ ➜  kubectl create -f replicaset-definition.yml 
replicaset.apps/myapp-replicaset created

controlplane ~ kubectl get replicaset
NAME               DESIRED   CURRENT   READY   AGE
myapp-replicaset   3         3         3       71s



controlplane ~ ➜  kubectl get pods
NAME                     READY   STATUS    RESTARTS   AGE
myapp-replicaset-9bhsj   1/1     Running   0          97s
myapp-replicaset-cbjgz   1/1     Running   0          97s
myapp-replicaset-vsj7l   1/1     Running   0          97s



HOW TO SCALE? how to unpdate it to 6
1. replicas: 6
kubectl replace -f replicaset-definition.yml 
2.
kubectl scale --replicas=6 -f replicaset-definition.yml


controlplane ~ ➜  kubectl delete replicasets replicaset-1 replicaset-2 
replicaset.apps "replicaset-1" deleted
replicaset.apps "replicaset-2" deleted


kubectl replace --image=6 


Name:         new-replica-set
Namespace:    default
Selector:     name=busybox-pod
Labels:       <none>
Annotations:  <none>
Replicas:     4 current / 4 desired
Pods Status:  0 Running / 4 Waiting / 0 Succeeded / 0 Failed
Pod Template:
  Labels:  name=busybox-pod
  Containers:
   busybox-container:
    Image:      busybox777
    Port:       <none>
    Host Port:  <none>
    Command:
      sh
      -c
      echo Hello Kubernetes! && sleep 3600
    Environment:  <none>
    Mounts:       <none>
  Volumes:        <none>
  
  
replicaset-definition.yml
-------------------------
controlplane ~ ➜  cat replicaset-definition.yml 
apiVersion: apps/v1
kind: ReplicaSet
metadata: 
  name: new-replica-set
  labels:
    app: busybox
    type: front-end
spec:
  template:
    # This is copy of one of the pods we created above
    # from metadata
    metadata: 
      name: busybox
      labels:
        app: busybox
        type: front-end
    spec:
      containers:
      - name: busybox
        image: busybox
  
  replicas: 4 # NUmber of replicas we need
  selector:
     matchLabels:
       type: front-end
  
  
# Can directly edit replicaset
kubectl edit replicaset new-replica-set

kubectl scale --replicas=6


===============DEPLOYEMTNS========================
-------------------------
deployment-definition.yml
-------------------------

apiVersion: apps/v1
kind: Deployment
metadata: 
  name: myapp-deployment
  labels:
    app: myapp
    type: front-end
spec:
  template:
    # This is copy of one of the pods we created above
    # from metadata
    metadata: 
      name: myapp-pod
      labels:
        app: myapp
        type: front-end
    spec:
      containers:
      - name: nginx-container
        image: nginx
  
  replicas: 3 # NUmber of replicas we need
  selector:
     matchLabels:
       type: front-end
  
  
  
kubectl create -f deployment-definition-1.yaml

controlplane ~ ➜  cat deployment-definition-1.yaml
---
apiVersion: apps/v1
kind: Deployment
metadata:
  name: deployment-1
spec:
  replicas: 2
  selector:
    matchLabels:
      name: busybox-pod
  template:
    metadata:
      labels:
        name: busybox-pod
    spec:
      containers:
      - name: busybox-container
        image: busybox
        command:
        - sh
        - "-c"
        - echo Hello Kubernetes! && sleep 3600


===============
My File:my.yml
===============
apiVersion: apps/v1
kind: Deployment
metadata:
  name: httpd-frontend
spec:
  replicas: 3
  selector:
    matchLabels:
      name: httpd-frontend
  template:
    metadata:
      labels:
        name: httpd-frontend
    spec:
      containers:
      - name: busybox-container
        image: httpd:2.4-alpine
        command:
        - sh
        - "-c"
        - echo Hello Kubernetes! && sleep 3600



controlplane ~ ➜  kubectl create -f my.yml 
deployment.apps/httpd-frontend created


========================================================
SERVICES
========================================================
service-definition.yml

apiVersion: apps/v1
kind: Service
metadata:
  name: httpd-frontend 
spec:
  type: ClusterIP
  ports:
    - targetPort: 6379
	  port: 6379
  selector:
     app: myapp
	 name: redis-pod


controlplane ~ kubectl get deployments
NAME                       READY   UP-TO-DATE   AVAILABLE   AGE
simple-webapp-deployment   4/4     4            4           20s

controlplane ~ ➜  kubectl describe deployment simple-webapp-deployment
Name:                   simple-webapp-deployment
Namespace:              default
...


---------------
service-definition-1.yaml
--------------
controlplane ~ ➜  cat service-definition-1.yaml 
apiVersion: v1
kind: Service
metadata:
  name: webapp-service
  namespace: default
spec:
  ports:
  - nodePort: 30080
    port: 8080
    targetPort: 8080
  selector:
    name: simple-webapp
  type: NodePort

==== annother service-definition.yml
controlplane ~ ➜  cat service-definition.yml 
apiVersion: v1
kind: Service
metadata:
  name: webapp-service
spec:
  type: NodePort
  ports:
    - targetPort: 80
      port: 8080
      nodePort: 30008
	  
controlplane ~ ➜  kubectl create -f service-definition.yml 
service/webapp-service created
	 
	 
Add selector to link service to pod (??)
	 
controlplane ~ ➜  cat service-definition.yml
apiVersion: v1
kind: Service
metadata:
  name: webapp-service
spec:
  type: NodePort
  ports:
    - targetPort: 80
      port: 8080
      nodePort: 30008
  selector:
    app: my-app
    type: front-end	 

controlplane ~ ➜  kubectl delete services webapp-service
service "webapp-service" deleted

controlplane ~ ➜  kubectl apply -f service-definition.yml 
service/webapp-service created

controlplane ~ kubectl describe service kubernetes
Name:              kubernetes
Namespace:         default
Labels:            component=apiserver
                   provider=kubernetes
Annotations:       <none>
Selector:          <none>
Type:              ClusterIP
IP Family Policy:  SingleStack
IP Families:       IPv4
IP:                10.43.0.1
IPs:               10.43.0.1
Port:              https  443/TCP
TargetPort:        6443/TCP
Endpoints:         192.5.100.3:6443
Session Affinity:  None
Events:            <none>

controlplane ~ ➜  kubectl get all


controlplane ~ ➜  kubectl create -f service-definition-1.yaml 
service/webapp-service created

controlplane ~ ➜  cat service-definition-1.yaml 
---
apiVersion: v1
kind: Service
metadata:
  name: webapp-service
  namespace: default
spec:
  ports:
  - nodePort: 30080
    port: 8080
    targetPort: 8080
  selector:
    name: simple-webapp
  type: NodePort
  

--=--BULDING APP STACK

docker run -d --name=redis redis
docker run -d --name=db postgres:9.4
docker run -d --name=vote -p 5000:80  voting-app
docker run -d --name=result -p 5001:80  result-app
docker run -d --name=worker worker

# link them all together
docker run -d --name=redis redis
docker run -d --name=db postgres:9.4
docker run -d --name=vote -p 5000:80  --link redis:redis voting-app
docker run -d --name=result -p 5001:80  --link db:db result-app
docker run -d --name=worker --link redis:redis --link db:db worker

# Deploy above on kubernetes
Goals: 
	deploy containesr
	enable connnectivity
	external access
	
We cannot deploy containers directly. We need pod.
Steps
1. Deploy PODs
2. Eneable connectivity between Services - Create sevices(clusterIP)
	1. redis
	2. db
3. Create Services (NodePort)
	1. Voting-app
	2. result-app
	










