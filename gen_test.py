with open("aadebugsql/multiple1.sql", "w") as file:
    file.write('create table d (id int, name char(16),test bigint,test2 bigint,test3 float);\n');
    file.write('create index d(id,test3);\n');
    file.write('create index d(test3,id);\n');
    file.write('create index d(test,id);\n');
    # for id in range(1,120000):
    for id in range(1,1001):
        file.write(f"insert into d values({id},'name',1,2,{id/1.7:.6f});\n");
    file.write('select * from d where test=1;');

with open("aadebugsql/bnlj1.sql", "w") as file:
    file.write('create table t1 (id int, name char(16),test bigint,test2 bigint,test3 float);\n');
    for id in range(1,101):
        file.write(f"insert into d values({id},'name',1,2,{id/1.7:.6f});\n");
    file.write('select * from d;\n');
    file.write('select * from d;\n');
    file.write('select * from d;\n');

with open("aadebugsql/txn1.sql", "w") as file:
    file.write('create table d (id int, name char(16),time datetime,test2 bigint,test3 float);\n');
    file.write('create index d(time);\n');
    file.write('create index d(id);\n');
    
    # 插10条 abort
    file.write('begin;\n');
    for id in range(1,10):
        file.write(f"insert into d values({id},'name','2023-07-0{id} 18:42:00',2,{id/1.7:.6f});\n");
    file.write('abort;\n');
    # file.write('select * from d;\n');
    # file.write('select * from d where id>0;\n');

    file.write('begin;\n');
    for id in range(1,10):
        file.write(f"insert into d values({id},'name','2023-07-0{id} 18:42:00',2,{id/1.7:.6f});\n");
    file.write('commit;\n');
    # file.write('select * from d;\n');
    # file.write('select * from d where id>0;\n');

    file.write('begin;\n');
    for id in range(1,10):
        file.write(f"update d set time='2023-08-0{id} 18:42:00' where time='2023-07-0{id} 18:42:00';\n");
    file.write('abort;\n');
    file.write('select * from d;\n');
    file.write('select * from d where id>0;\n');

    file.write('begin;\n');
    for id in range(1,10):
        file.write(f"update d set time='2023-08-0{id} 18:42:00' where time='2023-07-0{id} 18:42:00';\n");
    file.write('commit;\n');
    file.write('select * from d;\n');
    file.write('select * from d where id>0;\n');

    file.write('begin;\n');
    for id in range(1,10):
        file.write(f"delete from d where time='2023-08-0{id} 18:42:00';\n");
    file.write('abort;\n');
    file.write('select * from d;\n');
    file.write('select * from d where id>0;\n');

    file.write('begin;\n');
    for id in range(1,10):
        file.write(f"delete from d where time='2023-08-0{id} 18:42:00';\n");
    file.write('commit;\n');
    file.write('select * from d;\n');
    file.write('select * from d where id>0;\n');

    